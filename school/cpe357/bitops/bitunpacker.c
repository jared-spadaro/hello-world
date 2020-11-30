#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UINT_SIZE 32
#define UINT_MASK 0xFFFFFFFF
#define CHAR_SIZE 8
#define CHAR_MASK 0xFF

typedef unsigned int UInt;

/*
Have current int block and next int block
Returns a code through an out parameter
Return true if you can return a code return false if you need another int block
*/

typedef struct {
UInt curData;
UInt nextData;
int bitsLeft;
int validNext;
} BitUnpacker;

//BuInit
void BuInit (BitUnpacker *bu) {
   bu->curData = 0;
   bu->nextData = 0;
   bu->bitsLeft = 0;
   bu->validNext = 0;
}

//BuTakeData
void BuTakeData (BitUnpacker *bu, UInt data) {
   bu->nextData = data;
   bu->validNext = 1;
}

//Unpack
int BuUnpack (BitUnpacker *bu, UInt *out) {
   UInt mask;
   int shift, ret = 0;
   if(!bu->bitsLeft) {
      if(bu->validNext) {
         bu->curData = bu->nextData;
         bu->bitsLeft = UINT_SIZE;
         bu->validNext = 0;
      }
      else {
         ret = 0;
      }
   }
   if(bu->bitsLeft > 0) { //if there are bits left to be unpacked
      shift = bu->bitsLeft - CHAR_SIZE;
      mask = CHAR_MASK << shift;
      *out = (bu->curData & mask) >> shift;
      bu->bitsLeft -= CHAR_SIZE;
      ret = 1;      
   }
   return ret;
}
      

#define BYTESPERINT 4

int main() {
BitUnpacker bu;
int numBlocks, size, i, count;
UInt ret;
UInt *temp;

scanf("%d", &numBlocks);

temp = calloc(sizeof(UInt), numBlocks);

for (i = 0; i < numBlocks; i++) {
   scanf(" %x", &temp[i]);
}

BuInit(&bu);
i = 0;

count = numBlocks * BYTESPERINT;

while (count--) {
   if (!BuUnpack(&bu, &ret)) {
      if (i < numBlocks) {
         BuTakeData(&bu, temp[i++]);
         BuUnpack(&bu, &ret);
      }
      else {
         printf("Not enough data left.\n");
      }
   }
   printf("data: %02X\n", ret);
}
printf("\n");
free(temp);

return 0;
}
