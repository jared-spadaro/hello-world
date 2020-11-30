#include <stdio.h>

#define NUMVALS 6
#define SIZE 5
#define MAX 31

int main () {
   int vals = 0;
   short curVal, idx = 0;
   
   printf("Reading in values\n");
   //START MY CODE
   for(idx = 0; idx < NUMVALS; idx++) {
      scanf("%hd", &curVal);
      vals <<= SIZE;
      vals |= curVal;
   }
   printf("Value = %X\n", vals);
   return 0;
} 
