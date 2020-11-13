#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

void insertSort (int arr[], int size) {
   int i, j, key;
   for (i = 1; i < size; i++) {
      key = arr[i];
      j = i - 1;
      while (j >= 0 && arr[j] > key) {
         /* swap values */
         arr[j+1] = arr[j];
         arr[j--] = key;
      }
   }
}

/* takes two subarrays and swaps them if out of order */
void merge (int *arr, int left, int middle, int right) {
   /* placeholder for swapping subarrays */ 
   int i, *temp = malloc(sizeof(int));
   for (i = left; i <= middle; i++) { 
      if (arr[i] > arr[i + middle + 1]) { 
         memcpy(temp, &arr[i], 1);
         memcpy(&arr[i], &arr[i + middle + 1], 1);
         memcpy(&arr[i + middle + 1], temp, 1);
   }
}

void mergeSort (int arr[], int left, int right) {
   int middle;
   if (right > left) {
      middle = (left + right) / 2;
      mergeSort(arr, left, middle);
      mergeSort(arr, middle + 1, right);
      merge(arr, left, middle, right);
   }
}

void generateRandomArray (int *arr, int size) {
   int i;
   
   srand(time(NULL));
   for (i = 0; i < size; i++) {
      /* fill array with random integer values from 0 to 99 */
      arr[i] = rand() % 100;
   }
}

void printArray (int *arr, int size) {
   int i;
   for (i = 0; i < size; i++) {
      printf("%d ", arr[i]);
      if (i && !(i % 20)) {
         printf("\n");
      }
   }
   printf("\n");
}


int main (void) {
   int size, *arr;
   char type;

   printf("Enter i for insert sort or m for merge sort\n");
   scanf("%c", &type);
   printf("Enter size of array you would like to sort: ");
   scanf("%d", &size);
   arr = malloc(sizeof(int) * size);
   generateRandomArray(arr, size);
   
   printf("Random array values:\n");
   printArray(arr, size);

   if (type == 'i') {
      insertSort(arr, size);
   }
   else if (type == 'm') {
      mergeSort(arr, 0, size - 1);
   }
   else {
      fprintf(stderr, "Incorrect sort type entered\n");
      exit(1);
   }
   printf("Sorted array values:\n");
   printArray(arr, size);
   
   return 0;
}
