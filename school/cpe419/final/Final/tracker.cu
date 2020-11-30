#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <iostream>

#include "tracker.hpp"

#define MIN_FEATURES 30
#define FAST_THRESHOLD 50
#define FEATURE_POINT_SIZE 3
#define MAX_FRAMES 30
#define MASK_RADIUS 3
#define NUM_PIX 16
#define NUM_CONTIG 12
#define THREAD_SIZE 16

using namespace cv;
using namespace std;

__device__ int d_numCorners;

__global__ void fastDetector(uchar *d_ImGreyVec, uchar *d_contigCounts, 
 int thresh, int minContigCorner, int numRows, int numCols) {
    int tx = threadIdx.x, ty = threadIdx.y;
    int bx = blockIdx.x, by = blockIdx.y;

    int row = by*blockDim.y + ty;
    int col = bx*blockDim.x + tx;
    
    if (((row < (numRows - MASK_RADIUS)) && (row >= MASK_RADIUS)) &&
        ((col < (numCols - MASK_RADIUS)) && (col >= MASK_RADIUS))) {
        
        uchar cirPixels[16];
        int ndx = row * numCols + col;
        
        // variables to keep track the number of contiguous pixels of same label
        int contiguous = 0;
        int begContig = 0;
        int maxContig = 0;
        int beginning;

        // variable to hold result of comparison
        int compareResult;

        // Each thread examines pixel at Row y, Col x
        uchar centerPix = d_ImGreyVec[ndx];
        int maxThresh = centerPix + thresh;
        int minThresh = centerPix - thresh;

        /*
           Get pixel values along circle that are used to check if center
           pixel is a corner 
        */
        cirPixels[0] = d_ImGreyVec[ndx - 3];
        cirPixels[1] = d_ImGreyVec[ndx - numCols - 3];
        cirPixels[2] = d_ImGreyVec[ndx - (2 * numCols) - 2];
        cirPixels[3] = d_ImGreyVec[ndx - (3 * numCols) - 1];
        cirPixels[4] = d_ImGreyVec[ndx - (3 * numCols)];
        cirPixels[5] = d_ImGreyVec[ndx - (3 * numCols) + 1];
        cirPixels[6] = d_ImGreyVec[ndx - (2 * numCols) + 2];
        cirPixels[7] = d_ImGreyVec[ndx - (numCols) + 3];
        cirPixels[8] = d_ImGreyVec[ndx + 3];
        cirPixels[9] = d_ImGreyVec[ndx + (numCols) + 3];
        cirPixels[10] = d_ImGreyVec[ndx + (2 * numCols) + 2];
        cirPixels[11] = d_ImGreyVec[ndx + (3 * numCols) + 1];
        cirPixels[12] = d_ImGreyVec[ndx + (3 * numCols)];
        cirPixels[13] = d_ImGreyVec[ndx + (3 * numCols) - 1];
        cirPixels[14] = d_ImGreyVec[ndx + (2 * numCols) - 2];
        cirPixels[15] = d_ImGreyVec[ndx + (1 * numCols) - 3];

        for (int i = 0; i < NUM_PIX; i++) {
            compareResult = cirPixels[i] > maxThresh;
            contiguous = contiguous * compareResult + compareResult;
            if (beginning && contiguous == 0) {
                beginning = 0;
            }
            if (beginning) {
                begContig++;
            }
            if (contiguous > maxContig) {
                maxContig = contiguous;
            }
        }
        contiguous += begContig;
        if (maxContig < contiguous) {
            maxContig = contiguous;
        }

        for (int i = 0; i < NUM_PIX; i++) {
            compareResult = cirPixels[i] < minThresh;
            contiguous = contiguous * compareResult + compareResult;
            if (beginning && contiguous == 0) {
                beginning = 0;
            }
            if (beginning) {
                begContig++;
            }
            if (contiguous > maxContig) {
                maxContig = contiguous;
            }
        }
        contiguous += begContig;
        if (maxContig < contiguous) {
            maxContig = contiguous;
        }
        if (maxContig >= minContigCorner) {
            d_contigCounts[ndx] = maxContig;
        }
    }

}

int main(int argc, char** argv )
{
  /* Video Camera Object */
  VideoCapture cam;

  /* Video Frame Images */
  Mat frame, frame_gray, oldframe;
  uchar *imGreyPtr;

  /* Create vectors and/or pointers that reference host/device data */
  thrust::host_vector<uchar> h_ImGreyVec;
  thrust::device_vector<uchar> d_ImGreyVec;
  uchar *d_contigCounts;
  uchar *h_contigCounts;
  
  int numRows, numCols, size;

  /* Matrix for Rigid Transform */
  Mat rigid_transform;

  /* Feature Point Vectors */
  std::vector<KeyPoint> keypoints;
  std::vector<Point2f> pts, tracked_pts, prev_pts, saved_pts;

  /* Status and Error Flags for KLT Algorithm */
  std::vector<uchar> status;
  std::vector<float> err;

  /* Pixed Distance Calculation Variables */
  float dist_x = 0, dist_y = 0;

  /* Frame Counter */
  int frame_count = 0;

  /* Open Camera Device */
  cam.open("vid.mov");

  /* Check Camera Device Opens (Returns -1 on Error) */
  if (!cam.isOpened()) {
     return -1;
  }

  /* Create Window for Displaying Video Feed */
  namedWindow("Feature Tracking", WINDOW_NORMAL);

  cam >> frame;
  numRows = frame.rows;
  numCols = frame.cols;
  size = numRows*numCols;
  int goodSize = size;
  h_contigCounts = (uchar *)malloc(size * sizeof(uchar)); 
  /* initialize cuda kernel parameters */
  int gridSizeX = ((numRows-1) / THREAD_SIZE) + 1;
  int gridSizeY = ((numCols-1) / THREAD_SIZE) + 1;
  dim3 blockSize(THREAD_SIZE, THREAD_SIZE, 1);
  dim3 gridSize(gridSizeX, gridSizeY, 1);
  cudaMalloc((void **) &d_contigCounts, size * sizeof(uchar)); 
  uchar *d_ImGrey_raw;
  int error;

  /* Loop Forever Until Camera Closed */
  while (numRows) {
     /* Convert Frame to Grayscale */
     cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
     imGreyPtr = (uchar *)frame_gray.ptr<uchar>(0);
     h_ImGreyVec.assign(imGreyPtr, imGreyPtr + size);
     d_ImGreyVec = h_ImGreyVec;
     d_ImGrey_raw = thrust::raw_pointer_cast(&d_ImGreyVec[0]);
     fastDetector<<<gridSize, blockSize>>>(d_ImGrey_raw,        
      d_contigCounts, FAST_THRESHOLD, NUM_CONTIG, numRows, numCols);
     error = cudaDeviceSynchronize();
     /*imshow("Live View", frame);
     if (waitKey(1) >= 0) {
        break;
     }*/

     /* Obtain Frame from Camera */
     cam >> frame;
     numRows = frame.rows;
     numCols = frame.cols;
     size = numRows*numCols;
     frame_count++;
  }

  cout << "made it" << endl;
  cudaMemcpy(h_contigCounts, d_contigCounts, size * sizeof(uchar),
   cudaMemcpyDeviceToHost);
  for (int i = 0; i < 10; i++) {
    cout << h_contigCounts[i] << " ";
  }
  cout << "\n";
  cudaFree(d_contigCounts);
  
  return 0;
}
