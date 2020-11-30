#include <stdio.h>

void SquareArray (int *array, int dim) {
   int *iPtr;
   iPtr = array;  //same as saying iPtr = &array[0];
   while (array - iPtr < dim) {
      *array = *array * *array;
      array++;
   }
}

void PrintArray (int array[], int dim) {
   int i = 0;
   printf("Result: ");
   for (i=0; i<dim; i++) {
      printf("%d ", array[i]);
   }
   printf("\n");
}
      
int main (void) {
   int b;
   printf("Enter 5 numbers: ");
   int *iPtr;
   int myarray[5];
   iPtr = myarray;
   while(iPtr - myarray < 5) {
      scanf("%d", iPtr);
      iPtr++;
   }
   SquareArray(myarray,b=5);
   PrintArray(myarray,5);
   iPtr = myarray + 2;
   //printf("%d\n",iPtr[-1]);
   return 0;
} 
   










