#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

/* global variables shared by all functions/threads */
double **vals1;
double **vals2;
double **product;
int rows1, cols1, rows2, cols2, numthreads, iteration = 0;
double elapsed[5];

void *Multiply(void *);

/* read matrix files, multiply them, and print result to file */
void ReadAndMultiply () {
   int i, j;
   pthread_t *thread_handles;

   FILE *stream1 = fopen("matrix1", "r");
   FILE *stream2 = fopen("matrix2", "r");
   FILE *result = fopen("result", "w");
   
   /* read dimensions of matrices */
   fscanf(stream1, "%d %d", &rows1, &cols1);
   fscanf(stream2, "%d %d", &rows2, &cols2);

   /* data structures for holding matrices and result */
   vals1 = malloc(sizeof(double *) * rows1);
   vals2 = malloc(sizeof(double *) * rows2);
   product = malloc(sizeof(double *) * rows1);
   
   /* initialize data structures */
   for (i = 0; i < rows1; i++) {
      *(vals1 + i) = malloc(sizeof(double) * cols1);
      *(product + i) = malloc(sizeof(double) * cols2);
   }
   for (i = 0; i < rows2; i++) {
      *(vals2 + i) = malloc(sizeof(double) * cols2);
   }
   
   if (cols1 != rows2) {
      fprintf(stderr, "Dimensions of matrices do not allow for multiplication\n");
      exit(1);
   }

   /* read */
   for (i = 0; i < rows1; i++) {
      for (j = 0; j < cols1; j++) {
         fscanf(stream1, "%lf", *(vals1 + i) + j);
      }
   }
   for (i = 0; i < rows2; i++) {
      for (j = 0; j < cols2; j++) {
         fscanf(stream2, "%lf", *(vals2 + i) + j);
      }
   }

   /* create and setup threads */
   thread_handles = malloc(sizeof(pthread_t) * numthreads);
   for (i = 0; i < numthreads; i++) {
      pthread_create(thread_handles + i, NULL, Multiply, (void *)i);
   }
   
   for (i = 0; i < numthreads; i++) {
      pthread_join(*(thread_handles + i), NULL);
   }  
   free(thread_handles);
 
   /* sum results and print to file */
   for (i = 0; i < rows1; i++) {
      for (j = 0; j < cols2; j++) {
         fprintf(result, "%lf ", *(*(product + i) + j));
      }
      fprintf(result, "\n");
   }
   
}

/* thread function. each thread will perform multiplication on some number of rows.
 * timing of the multiplication occurs here.
 */
void *Multiply(void *id) {
   int i, j, k;
   int range, first, last;
   struct timespec begin, end;
   int thread_id = (int)id;   
   clock_gettime(CLOCK_THREAD_CPUTIME_ID, &begin);
   
   /* every thread except the last one */
   if (thread_id < numthreads - 1) {
      range = rows1 / numthreads;
      first = thread_id * range; 
      last = first + range;
   }
   else {  /* last thread must take care of remainder of rows */
      range = rows1 / numthreads;
      first = thread_id * range;
      last = first + range;
      range += (rows1 - last);
      last = first + range;
   }
  
   /* multiply the matrices */
   for (i = first; i < last; i++) {
      *(*(product + i)) = 0;
      for (j = 0; j < cols2; j++) {
         for (k = 0; k < cols1; k++) {
            *(*(product + i) + j) += *(*(vals1 + i) + k) * *(*(vals2 + k) + j);
         }
      }
   }    
   
   clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
   elapsed[iteration] = end.tv_sec - begin.tv_sec;
   elapsed[iteration] += (end.tv_nsec - begin.tv_nsec) / 1000000000.0;
  
   /* print time elapsed */
   if (thread_id == 0) {
      printf("Time %d = %lf\n", iteration, elapsed[iteration]);
   }
   return NULL;
}

int main (int argc, char **argv) {
   int n;
   double total = 0, average;
   if (argc < 2) {
      fprintf(stderr, "Usage: ./mult [numthreads]\n");
      exit(1);
   }
   numthreads = strtol(argv[1], NULL, 10); /* number of threads given by user */
   for (n = 0; n < 5; n++) {
      ReadAndMultiply();
      iteration++;
   }
   /* average times and print average */
   for (n = 0; n < 5; n++) {
      total += elapsed[n];
   }
   average = total / n;
   printf("Avg Time = %lf\n", average);
   
   return 0;
}
