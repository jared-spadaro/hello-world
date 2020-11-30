/*
 ============================================================================
 Name        : OpenCVCUDA.cu
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : CUDA compute reciprocals
 ============================================================================
 */

/*
 ============================================================================
 Name        : OpenCVCu.cu
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : CUDA compute reciprocals
 ============================================================================
 */
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <numeric>
#include <stdlib.h>


cv::Mat imageRGBA;
cv::Mat imageGrey;
uchar4        *d_rgbaImage__;

unsigned char *d_greyImage__;

size_t numRows() { return imageRGBA.rows; }
size_t numCols() { return imageRGBA.cols; }

//returns a pointer to an RGBA version of the input image
//and a pointer to the single channel grey-scale output
//on both the host and device

//Histogram: allocates host and device arrays for histogram
void preProcess(uchar4 **inputImage, unsigned char **greyImage,
                uchar4 **d_rgbaImage, unsigned char **d_greyImage,
                unsigned char **histogram, unsigned char **d_histogram,
                const std::string &filename) {
	//make sure the context initializes ok
	cudaFree(0);
	cv::Mat image;
	image = cv::imread(filename.c_str(), CV_LOAD_IMAGE_COLOR);
	if (image.empty()) {
		std::cerr << "Couldn't open file: " << filename << std::endl;
		exit(1);
	}

	cv::cvtColor(image, imageRGBA, CV_BGR2RGBA);

	//allocate memory for the output
	imageGrey.create(image.rows, image.cols, CV_8UC1);
	//This shouldn't ever happen given the way the images are created
	//at least based upon my limited understanding of OpenCV, but better to check
	if (!imageRGBA.isContinuous() || !imageGrey.isContinuous()) {
		std::cerr << "Images aren't continuous!! Exiting." << std::endl;
		exit(1);
	}
	*inputImage = (uchar4 *)imageRGBA.ptr<unsigned char>(0);
	*greyImage  = imageGrey.ptr<unsigned char>(0);
	const size_t numPixels = numRows() * numCols();
	//allocate memory on the device for both input and output
	cudaMalloc(d_rgbaImage, sizeof(uchar4) * numPixels);
	cudaMalloc(d_greyImage, sizeof(unsigned char) * numPixels);
	cudaMemset(*d_greyImage, 0, numPixels * sizeof(unsigned char)); //make sure no memory is left laying around

        //Histogram allocation. We need arrays of size numPixels 
        *histogram = (unsigned char *)calloc(sizeof(unsigned char), 256);
        cudaMalloc(d_histogram, sizeof(unsigned char) * 256); 
        cudaMemset(*d_histogram, 0, sizeof(unsigned char) * numPixels);

	//copy input array to the GPU
	cudaMemcpy(*d_rgbaImage, *inputImage, sizeof(uchar4) * numPixels,cudaMemcpyHostToDevice);
	d_rgbaImage__ = *d_rgbaImage;
	d_greyImage__ = *d_greyImage;
}

void postProcess(const std::string& output_file, unsigned char *eq_image) {
	const int numPixels = numRows() * numCols();
	//copy the output back to the host
	cudaMemcpy(d_greyImage__, eq_image, sizeof(unsigned char) * numPixels, cudaMemcpyHostToDevice); 
        cudaMemcpy(imageGrey.ptr<unsigned char>(0), d_greyImage__, sizeof(unsigned char) * numPixels, cudaMemcpyDeviceToHost);
        //output the image
	cv::imwrite(output_file.c_str(), imageGrey);
	cv::imshow ("Output Image", imageGrey);
	cv::waitKey(0);
	//cleanup
	cudaFree(d_rgbaImage__);
	cudaFree(d_greyImage__);
}

void referenceCalculation(const uchar4* const rgbaImage,
                          unsigned char *const greyImage,
                          size_t numRows,
                          size_t numCols)
{
	for (size_t r = 0; r < numRows; ++r) {
		for (size_t c = 0; c < numCols; ++c) {
			uchar4 rgba = rgbaImage[r * numCols + c];
			float channelSum = .299f * rgba.x + .587f * rgba.y + .114f * rgba.z;
			greyImage[r * numCols + c] = channelSum;
		}
	}
}

__global__
void rgba_to_greyscale(const uchar4* const rgbaImage,
                       unsigned char* const greyImage,
                       int numRows, int numCols)
{
	//Fill in the kernel to convert from color to greyscale
	//the mapping from components of a uchar4 to RGBA is:
	// .x -> R ; .y -> G ; .z -> B ; .w -> A
	//
	//The output (greyImage) at each pixel should be the result of
	//applying the formula: output = .299f * R + .587f * G + .114f * B;
	//Note: We will be ignoring the alpha channel for this conversion
	//First create a mapping from the 2D block and grid locations
	//to an absolute 2D location in the image, then use that to
	//calculate a 1D offset.

	int row= blockIdx.y * blockDim.y + threadIdx.y; // row Number
	int col = blockIdx.x * blockDim.x + threadIdx.x; // col Number
	if( row < numRows || col < numCols ){
			int i = row*numCols+col;
			uchar4 rgba = rgbaImage[ i ];
			float channelSum = .299f * rgba.x + .587f * rgba.y + .114f * rgba.z;
			greyImage[ i ] = channelSum;
	}
}
void your_rgba_to_greyscale(const uchar4 * const h_rgbaImage,
                            uchar4 * const d_rgbaImage,
                            unsigned char* const d_greyImage,
                            size_t numRows,
                            size_t numCols)
{
	int threadSize=32;
	int gridSizeX=((numRows-1)/threadSize)+1;
	int gridSizeY=((numCols-1)/threadSize)+1;
	const dim3 blockSize(threadSize, threadSize, 1);  //TODO
	const dim3 gridSize(gridSizeY, gridSizeX, 1);  //TODO
	rgba_to_greyscale<<<gridSize, blockSize>>>(d_rgbaImage,d_greyImage,numRows,numCols);
	cudaDeviceSynchronize(); cudaGetLastError();
}

__global__ void histogram_kernel (unsigned char *d_histogram, unsigned char *d_greyImage, 
 int numRows, int numCols) {
   int row= blockIdx.y * blockDim.y + threadIdx.y; // row Number
   int col = blockIdx.x * blockDim.x + threadIdx.x; // col Number
   if( row < numRows || col < numCols ){
      int i = row*numCols+col;
      //atomicAdd((int *)(d_histogram + d_greyImage[i]), 1);  
      	d_histogram[d_greyImage[i]]++;
   }
}

void normalizeHistogram(unsigned char *histogram) {
   int i;
   int *c_histogram = (int *)calloc(sizeof(int),  256);
   int running_total = 0;
   for (i = 0; i < 256; i++) {
      running_total += histogram[i];
      c_histogram[i] = running_total;
   }
   for (i = 0; i < 256; i++) {
      printf("%d ", c_histogram[i]);
   }
   printf("\n\n");
   //now normalize
   for (i = 0; i < 256; i++) {
      histogram[i] = ((c_histogram[i] - 1) * 255) / (numRows() * numCols());
   }
   for (i = 0; i < 256; i++) {
      printf("%d ", histogram[i]);
   }
   printf("\n");
}
   

void createHistogram(unsigned char *histogram, unsigned char *d_histogram, unsigned char *d_greyImage,
 size_t numRows, size_t numCols) {
   int threadSize = 32, ndx = 0, numPixels = 0;
   int gridSizeX = ((numRows-1)/threadSize)+1;
   int gridSizeY = ((numCols-1)/threadSize)+1;
   const dim3 blockSize(threadSize, threadSize, 1);
   const dim3 gridSize(gridSizeY, gridSizeX, 1);
   histogram_kernel<<<gridSize, blockSize>>>(d_histogram, d_greyImage, numRows, numCols);
   cudaDeviceSynchronize(); cudaGetLastError();
   cudaMemcpy(histogram, d_histogram, sizeof(unsigned char) * 256, cudaMemcpyDeviceToHost);
   for(ndx = 0; ndx < 256; ndx++) {
      printf("%d ", histogram[ndx]);
      numPixels += histogram[ndx];
   }
   printf("\n");
   printf("%d\n", numPixels);
   printf("\n");
   normalizeHistogram(histogram);
}

int main(int argc, char **argv) {
	uchar4        *h_rgbaImage, *d_rgbaImage;
	unsigned char *h_greyImage, *d_greyImage;
        unsigned char *histogram, *d_histogram, *eq_image;
        int i;
	std::string input_file;
	std::string output_file;
	if (argc == 3) {
		input_file  = std::string(argv[1]);
		output_file = std::string(argv[2]);
	}
	else {
		std::cerr << "Usage: ./hw input_file output_file" << std::endl;
		exit(1);
	}
	//load the image and give us our input and output pointers
	preProcess(&h_rgbaImage, &h_greyImage, &d_rgbaImage, &d_greyImage, 
         &histogram, &d_histogram, input_file);
	//call the students' code
	your_rgba_to_greyscale(h_rgbaImage, d_rgbaImage, d_greyImage, numRows(), numCols());
        //h_greyImage = (unsigned char *)calloc(numPixels, sizeof(unsigned char));
	const size_t numPixels = numRows() * numCols();
        eq_image = (unsigned char *)calloc(numPixels, sizeof(unsigned char));
	cudaMemcpy(h_greyImage, d_greyImage__, sizeof(unsigned char) * numPixels, cudaMemcpyDeviceToHost);
        //BUILD HISTOGRAM HERE (write kernel, call it here)
        createHistogram(histogram, d_histogram, d_greyImage, numRows(), numCols());
        printf("sample histogram value = %d\n", histogram[27]);
        //for (i = 0; i < numPixels; i++) {
          // printf("%d ", h_greyImage[i]);
        //} 
        printf("\n");
        for (i = 0; i < numPixels; i++) {
           eq_image[i] = histogram[h_greyImage[i]];
           printf("%d ", eq_image[i]);
        }
        //printf("\n");
	cudaDeviceSynchronize();
	cudaGetLastError();
	printf("\n");
	//check results and output the grey image
	postProcess(output_file, eq_image);
	return 0;
}

