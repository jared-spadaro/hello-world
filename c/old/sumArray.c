#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

void sumArray(int *input, int *output) {
   int i,j;
   for (i = 0; i < SIZE; i++) {
      for (j = 0; j < SIZE; j++) {
         if (j != i) output[i] += input[j];
      }
   }
}

void driver() {
   int *input = calloc(sizeof(int), SIZE);
   int *output = calloc(sizeof(int), SIZE);
   printf("Enter 10 integers.\n");
   int i;
   for (i = 0; i < SIZE; i++) {
      scanf("%d", &input[i]);
   }
   sumArray(input, output);
   printf("Sum array = ");
   for (i = 0; i < SIZE; i++) {
      printf("%d ", output[i]);
   }
   printf("\n");
}


int main(void) {
   driver();  
   return 0;    
}
