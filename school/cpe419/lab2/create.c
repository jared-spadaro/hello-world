#include <stdio.h>
#include <stdlib.h>

#define ROWS1 10
#define COLS1 10
#define ROWS2 10
#define COLS2 10

#define MATRIX_SIZE 2 * 2
#define MAX_VALUE 100

void CreateMatrix (int numRows, int numCols, char *name, int seed) {
   int i,j;
   double r;
   FILE *stream = fopen(name, "w");
   srand(seed);
   for (i = 0; i < numRows; i++) {
      for(j = 0; j < numCols; j++) {
         r = (double)rand()/(double)(RAND_MAX/MAX_VALUE);
         fprintf(stream, "%lf ", r);
      }
      fprintf(stream, "\n");
   }
}

int main (int argc, char **argv) {
   if (argc < 2) {
      fprintf(stderr, "Usage: seed\n");
      exit(1);
   }
   int seed = strtol(argv[1], NULL, 10);
   CreateMatrix(ROWS1, COLS1, "matrix1", seed);
   CreateMatrix(ROWS2, COLS2, "matrix2", seed/2);
   return 0;
}
