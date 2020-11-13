#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

#define MAX_FNAME_LEN 50
#define NUM_ADJ 13

unsigned long multiply (char *input, int size) {
   int i;
   unsigned long ret = 1;
   for (i = 0; i < size; i++) {
      printf("%lu\n", ret);
      ret *= (input[i] - '0');
   }
   printf("\n");
   return ret;
}
unsigned long readFile() {
   FILE *file = fopen("infile.txt", "r");
   char nums[NUM_ADJ];
   int i;
   unsigned long curr = 0, max = 0;
   //read first 13 numbers and store in nums
   for (i = 0; i < NUM_ADJ; i++) {
      fread(&nums[i], sizeof(char), 1, file);
   }
   curr = multiply(nums, NUM_ADJ);
   max = curr;
   
   /* 
      read one additional number at a time, 
      replacing first number in sequence.
      then multiply and compare against max 
   */
   i = 0;
   while (!feof(file)) {
      fread(&nums[i], sizeof(char), 1, file);
      curr = multiply(nums, NUM_ADJ);
      if (curr > max) max = curr;
      i++;
      if (i > 12) i = 0;
      printf("curr = %lu\n", curr);
   }
   return max;
}

int main(void) {
   printf("Max = %lu\n", readFile());
   return 0;
}


