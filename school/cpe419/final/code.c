#include <stdlib.h>
#include <stdio.h>

#define ROWS 120
#define COLS 80
#define N 16
#define COORD 0

/* to do: find COORD via thread index (each thread gets a pixel) */ 
void createArray (int *cirPixels, int *d_ImGreyVec) {
   int numCols = 0;  

   cirPixels[0] = d_ImGreyVec[COORD - 3] 
   cirPixels[1] = d_ImGreyVec[COORD - numCols - 3];
   cirPixels[2] = d_ImGreyVec[COORD - (2 * numCols) - 2]; 
   cirPixels[3] = d_ImGreyVec[COORD - (3 * numCols) - 1];
   cirPixels[4] = d_ImGreyVec[COORD - (3 * numCols)];
   cirPixels[5] = d_ImGreyVec[COORD - (3 * numCols) + 1]; 
   cirPixels[6] = d_ImGreyVec[COORD - (2 * numCols) + 2]; 
   cirPixels[7] = d_ImGreyVec[COORD - numCols + 3]; 
   cirPixels[8] = d_ImGreyVec[COORD + 3] 
   cirPixels[9] = d_ImGreyVec[COORD + numCols + 3] 
   cirPixels[10] = d_ImGreyVec[COORD + (2 * numCols) + 2]; 
   cirPixels[11] = d_ImGreyVec[COORD + (3 * numCols) + 1]; 
   cirPixels[12] = d_ImGreyVec[COORD + (3 * numCols)]; 
   cirPixels[13] = d_ImGreyVec[COORD + (3 * numCols) - 1];
   cirPixels[14] = d_ImGreyVec[COORD + (2 * numCols) - 2]; 
   cirPixels[15] = d_ImGreyVec[COORD + numCols - 3]; 
}

int main (void) {
   int *cirPixels = malloc(sizeof(int) * N);
   int *d_ImGreyVec = malloc(sizeof(int) * ROWS * COLS);
   
