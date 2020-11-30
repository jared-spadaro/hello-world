#include <stdio.h>
#include <stdlib.h>

#define MATRIX_SIZE 2 * 2
#define MAX_VALUE 100

/* function to create the matrix files. the dimensions are given as
 * commandline arguments, as is the seed for the random numbers
 * in the matrices.
 */
void CreateMatrix (int numRows, int numCols, char *name, int seed) {
   int i,j;
   double r;
   FILE *stream = fopen(name, "w");
   fprintf(stream, "%d %d\n", numRows, numCols); /* put dimensions at start of file */
   srand(seed); /* seed rand(3) with a user-inputted number */
   for (i = 0; i < numRows; i++) {
      for(j = 0; j < numCols; j++) {
         r = (double)rand()/(double)(RAND_MAX/MAX_VALUE);  /* get pseudorandom number with max value of 100 */
         fprintf(stream, "%lf ", r); /* print pseudorandom number to file */
      }
      fprintf(stream, "\n"); /* add new lines to make file look like matrix */
   }
}

int main (int argc, char **argv) {
   if (argc < 6) {
      fprintf(stderr, "Usage: rows1 cols1 rows2 cols2 seed\n");
      exit(1);
   }
   /* dimensions and seed are given by user */
   int rows1 = strtol(argv[1], NULL, 10);
   int cols1 = strtol(argv[2], NULL, 10);
   int rows2 = strtol(argv[3], NULL, 10);
   int cols2 = strtol(argv[4], NULL, 10);
   int seed = strtol(argv[5], NULL, 10);
   /* create matrices */
   CreateMatrix(rows1, cols1, "matrix1", seed);
   CreateMatrix(rows2, cols2, "matrix2", seed/2);
   return 0;
}
