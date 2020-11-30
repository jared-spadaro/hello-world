#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* read matrix files, multiply, and print result */
void ReadAndMultiply () {
   int n, i, j, k, rows1, cols1, rows2, cols2;
   double sum = 0;   
   struct timespec begin, end;
   double total = 0, elapsed[5];

   FILE *stream1 = fopen("matrix1", "r");
   FILE *stream2 = fopen("matrix2", "r");
   FILE *result = fopen("result", "w");
   fscanf(stream1, "%d %d", &rows1, &cols1);
   fscanf(stream2, "%d %d", &rows2, &cols2);

   /* data structures to hold matrices and result */
   double **vals1 = malloc(sizeof(double *) * rows1);
   double **vals2 = malloc(sizeof(double *) * rows2);
   double **product = malloc(sizeof(double *) * rows1);
   
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
   
   /* loop for running 5 iterations and averaging the runtime */
   for (n = 0; n < 5; n++) {
      clock_gettime(CLOCK_THREAD_CPUTIME_ID, &begin);
      /* multiply */
      for (i = 0; i < rows1; i++) {
         for (j = 0; j < cols2; j++) {
            for (k = 0; k < rows2; k++) {
               sum = sum + *(*(vals1 + i) + k) * *(*(vals2 + k) + j);
            }
         *(*(product + i) + j) = sum;
         sum = 0;
         } 
      }
      clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
      elapsed[n] = end.tv_sec - begin.tv_sec;
      elapsed[n] += (end.tv_nsec - begin.tv_nsec) / 1000000000.0;
   }
   /* print and average times */
   for (n = 0; n < 5; n++) {
      printf("elapsed time %d = %lf\n", n, elapsed[n]);
      total += elapsed[n];
   }
   printf("average time = %lf\n", total/5); 

   /* print product to file */
   for (i = 0; i < rows1; i++) {
      for (j = 0; j < cols2; j++) {
         fprintf(result, "%lf ", product[i][j]);
      }
      fprintf(result, "\n");
   }
}

int main (void) {
   ReadAndMultiply();
   return 0;
}
