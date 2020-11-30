#include <stdio.h>
#include <stdlib.h>

#define NUMVALS 6
#define MAX 31
#define SIZE 5

int read () {
   int vals = 0;
   short curVal, idx = 0;
   printf("Reading in shorts...\n");
   while(idx <= SIZE) {
      scanf("%hu", &curVal);
      vals |= curVal;
      if(idx!=5) vals <<= SIZE;
      idx++;
   }
   printf("Vals (FINAL) = %X\n", vals);
   return vals;
}

void print (int vals) {
   short curVal, idx = 5;
   //printf("Vals = %X\n", (vals >> 5) & 0x0000001F);
   //printf("Vals = %X\n", vals);
   while(idx >= 0) {
      printf("%d ", (vals >> idx * SIZE) & 0x0000001F);   
      idx--; 
   }
   printf("\n");
}
      
int main (void) {
   print(read());
   return 0;
}
