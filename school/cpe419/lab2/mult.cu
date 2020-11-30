#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define ROWS1 10
#define COLS1 10
#define ROWS2 10
#define COLS2 10

#define NUMTHREADS 16

/* global variables shared by all functions/threads */
double **h_vals1, **h_vals2;
double **d_vals1, **d_vals2;
double **h_product;
double **d_product;

void *Multiply(void *);

void InitializeDeviceMem () {
   int i;
   cudaMalloc((void ***)&d_vals1, sizeof(double *) * ROWS1);
   cudaMalloc((void ***)&d_vals2, sizeof(double *) * ROWS2);
   cudaMalloc((void ***)&d_product, sizeof(double *) * ROWS1);
   
   /* initialize data structures */
   for (i = 0; i < ROWS1; i++) {
      cudaMalloc((void **)(d_vals1 + i), sizeof(double) * COLS1);
      cudaMalloc((void **)(d_product + i), sizeof(double) * COLS2);
   }
   for (i = 0; i < ROWS2; i++) {
      cudaMalloc((void **)(d_vals2 + i), sizeof(double) * COLS2);
   }

   cudaMemcpy(d_vals1, h_vals1, xxxYYY);
}


/* read matrix files, multiply them, and print result to file */
void Read () {
   int i, j;

   FILE *stream1 = fopen("matrix1", "r");
   FILE *stream2 = fopen("matrix2", "r");
   FILE *result = fopen("result", "w");
   
   /* data structures for holding matrices and result */
   h_vals1 = (double **)malloc(sizeof(double *) * ROWS1);
   h_vals2 = (double **)malloc(sizeof(double *) * ROWS2);
   h_product = (double **)malloc(sizeof(double *) * ROWS1);
   
   /* initialize data structures */
   for (i = 0; i < ROWS1; i++) {
      *(h_vals1 + i) = (double *)malloc(sizeof(double) * ROWS1);
      *(h_product + i) = (double *)malloc(sizeof(double) * ROWS2);
   }
   for (i = 0; i < ROWS2; i++) {
      *(h_vals2 + i) = (double *)malloc(sizeof(double) * COLS2);
   }
   
   if (COLS1 != ROWS2) {
      fprintf(stderr, "Dimensions of matrices do not allow for multiplication\n");
      exit(1);
   }

   /* read */
   for (i = 0; i < ROWS1; i++) {
      for (j = 0; j < COLS1; j++) {
         fscanf(stream1, "%lf", *(h_vals1 + i) + j);
      }
   }
   for (i = 0; i < ROWS2; i++) {
      for (j = 0; j < COLS2; j++) {
         fscanf(stream2, "%lf", *(h_vals2 + i) + j);
      }
   }
}

/* thread function. each thread will perform multiplication on some number of rows.
 * timing of the multiplication occurs here.
 */
__global__ void Multiply(double **d_vals1, double **d_vals2, double **d_product, int width) {
   int i;
   //int range, first, last;
   //struct timespec begin, end;
   //int thread_id = (int)id;   
   //double elapsed;
   
   //clock_gettime(CLOCK_THREAD_CPUTIME_ID, &begin);
   
   int row = blockIdx.y * blockDim.y + threadIdx.y;
   int col = blockIdx.x * blockDim.x + threadIdx.x;

   double result = 0;

   for (i = 0; i < width; i++) {
      result += d_vals1[row][i] * d_vals2[i][col];
   }
   
   d_product[row][col] = result;

   //clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
   //elapsed = end.tv_sec - begin.tv_sec;
   //elapsed += (end.tv_nsec - begin.tv_nsec) / 1000000000.0;
  
   /* print time elapsed */
   //printf("Time = %lf\n", elapsed);
}

int main (int argc, char **argv) {
   //double time = 0;
   Read(); /* host memory is allocated and initialized here */
   InitializeDeviceMem(); /* device memory is allocated here */
   Multiply<<<(COLS1/NUMTHREADS, COLS1/NUMTHREADS), (NUMTHREADS, NUMTHREADS)>>>
    (d_vals1, d_vals2, d_product, COLS1);   
   int i, j;
   for (i = 0; i < ROWS1; i++) {
      for (j = 0; j < COLS2; j++) {
         printf("%lf", d_product[i][j]);
      }
   }
   return 0;
}
