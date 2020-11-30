#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SmartAlloc.h"

// ReadBlock
int *ReadBlock () {
   int i = 0, length = 1, curr[100];
   while(length) {
      scanf("%d", &curr[i]);
      if(curr[i] == 0) {
         length = 0;
      }
      i++;
   }
   length = i;
   int *final = malloc(sizeof(int) * length);
   for(i=0; i < length; i++) {
      *(final + i) = curr[i];
   }
   return final;
}

// CmpBlocks
int CmpBlocks (int *block1, int *block2) {
   while(*block1 && *block2 && *block1 == *block2) { 
      block1++;
      block2++;
   }
   return *block1 - *block2;
}
      

int main() {
int *block1, *block2;
int res;

block1 = ReadBlock();
block2 = ReadBlock();
printf("Space: %d\n", report_space());
res = CmpBlocks(block1, block2);
if (res == 0)
printf("Blocks are equal\n");
else
printf("%s is larger\n", res > 0 ? "block1" : "block2");

free(block1);
free(block2);
return 0;
}
