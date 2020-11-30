/*
 ============================================================================
 Name        : ImageBlur.cu
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : CUDA compute reciprocals
 ============================================================================
 */

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <numeric>
#include <stdlib.h>
//This code does Convolution on an array
//it has thw two implementations 2D and 2 pass 1D convolution
//the filter is just a [1 1 1 1 1]
//you should change it to your desired filte
#define BLUR_SIZE 5
#define TILE_WIDTH 16
__constant__ float M_d[BLUR_SIZE];

__global__ void convolution_1D_basic(float *P, float *N,int width){
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  float PValue=0;
  int N_start_point=i-(BLUR_SIZE/2);
  for(int j=0; j<BLUR_SIZE; j++){
	  if (N_start_point+j>=0 && N_start_point+j < width) {
		  PValue += N[N_start_point+j]*M_d[j];
	  }
  }
  //printf("thread %d %lf \n",i,PValue);
  P[i]=PValue/BLUR_SIZE;
}

__global__ void blurKernel(float *out, float *in, int width, int height) {

  int col = blockIdx.x * blockDim.x + threadIdx.x;
  int row = blockIdx.y * blockDim.y + threadIdx.y;
  if (col < width && row < height) {
    float pixVal = 0; //when change into read an image this should be an integer
    int pixels = 0;

    // Get the average of the surrounding BLUR_SIZE x BLUR_SIZE box
    for (int blurrow = -BLUR_SIZE; blurrow < BLUR_SIZE + 1; ++blurrow) {
      for (int blurcol = -BLUR_SIZE; blurcol < BLUR_SIZE + 1; ++blurcol) {
    	int currow = row + blurrow;
        int curcol = col + blurcol;
        // Verify we have a valid image pixel
        if (currow > -1 && currow < height && curcol > -1 && curcol < width) {
          pixVal += in[currow * width + curcol];
          pixels++; // Keep track of number of pixels in the avg
         }
      }
    }
    // Write our new pixel value out
    //out[row * width + col] = (unsigned char)(pixVal / pixels); // when changed into a image input do this
    out[row * width + col] = (pixVal / pixels);
  }
}

int main(int argc, char *argv[]) {


	unsigned int imageWidth=64;
	unsigned int imageHeight=64;
	dim3 dimsA(imageHeight,imageHeight);
	unsigned int size_A=dimsA.x*dimsA.y;
	unsigned int mem_size_A=sizeof(float)*size_A;


	//allocate mem for the host data
	float *hostInputImageData=(float *)malloc(mem_size_A);
	float *hostOutputImageData=(float *)malloc(mem_size_A);;

	//init array in host //in future this will be reading from an image
	for(int i=0; i<size_A;i++){
		hostInputImageData[i]=0.5f;
		hostOutputImageData[i]=0.0f;
	}
	//@@@ Debug code  print input image just to make sure we a reading non garbage
	//for(int i=1; i<size_A;i++)
	//		printf("input %i = %lf\n", i,hostOutputImageData[i]);


	//allocate mem for GPU Data
	float *deviceInputImageData;
	float *deviceOutputImageData;
	cudaMalloc((void **)&deviceInputImageData, mem_size_A);
	cudaMalloc((void **)&deviceOutputImageData, mem_size_A);

	//copy from the CPU memory to the GPU Memory
	cudaMemcpy(deviceInputImageData, hostInputImageData,mem_size_A,cudaMemcpyHostToDevice);

	//@@@@ Doing computation on the GPU 2D Image blur
	//dim3 dimGrid(ceil((float)imageWidth / TILE_WIDTH),ceil((float)imageHeight / TILE_WIDTH));
	//dim3 dimBlock(TILE_WIDTH, TILE_WIDTH);
	//@@@ Debug print dimGrid and block
	//printf("dimBlock=%d dimGrid=%d", dimBlock.x, dimGrid.x);
	//blurKernel<<<dimGrid, dimBlock>>>(deviceOutputImageData, deviceInputImageData, dimsA.x,dimsA.y);

	//@@@ Doing computation on the GPU for the 1D Image blur rows
	float M_h[5]={1,1,1,1,1};
	cudaMemcpyToSymbol(M_d,M_h, BLUR_SIZE*sizeof(float));
	int dimGrid=(ceil((float)size_A / TILE_WIDTH));
	int dimBlock=TILE_WIDTH;
	printf("dimBlock=%d dimGrid=%d", dimBlock, dimGrid);
	//rows
	convolution_1D_basic<<<dimGrid, dimBlock>>>(deviceOutputImageData, deviceInputImageData, size_A);
	cudaDeviceSynchronize();cudaGetLastError();
	//@@@ Debug code print new array blurred
	//for(int i=1; i<size_A;i++)
	//	printf("\n%lf",hostOutputImageData[i]);
	//cols
	float *deviceOutputImageDataCol;
	cudaMalloc((void **)&deviceOutputImageDataCol, mem_size_A);

	convolution_1D_basic<<<dimGrid, dimBlock>>>(deviceOutputImageDataCol, deviceOutputImageData, size_A);
	cudaDeviceSynchronize();cudaGetLastError();

	//done with computation on GPU so copy back to CPU
	cudaMemcpy(hostOutputImageData, deviceOutputImageData,imageWidth * imageHeight * sizeof(float),cudaMemcpyDeviceToHost);

	//free memory from cuda
	cudaFree(deviceInputImageData);
	cudaFree(deviceOutputImageData);

	//@@@ Debug code print new array blurred
	for(int i=1; i<size_A;i++)
		printf("\n%lf",hostOutputImageData[i]);
	//free CPU memory
	delete(hostInputImageData);
	delete(hostOutputImageData);
	return 0;


}
