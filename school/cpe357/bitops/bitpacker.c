#include <stdio.h>
#include "SmartAlloc.h"

#define UINT_SIZE 32
#define CHAR_SIZE 8

typedef unsigned char UChar;
typedef unsigned int UInt;

typedef struct {
UInt packedData;
int bitsUsed;
} BitPacker;

//BpInit
void BpInit (BitPacker *bp) {
   bp->packedData = 0;
   bp->bitsUsed = 0;
}

//BpPack
void BpPack (BitPacker *bp, UChar newByte, UChar isLast) {
   if(bp->bitsUsed < UINT_SIZE) { 
      bp->packedData <<= CHAR_SIZE; 
      bp->packedData |= newByte;
      bp->bitsUsed += CHAR_SIZE;
   }
   if(bp->bitsUsed == UINT_SIZE || isLast) { 
      bp->packedData <<= UINT_SIZE - bp->bitsUsed;
      printf("%X ", bp->packedData);
      BpInit(bp);
   }
}

int main() {
int count;
UChar data;
BitPacker bp;
BpInit(&bp);

scanf("%d", &count);

while (count--) {
scanf(" %c", &data);
BpPack(&bp, data, count == 0);
}

printf("\n");
return 0;
}
