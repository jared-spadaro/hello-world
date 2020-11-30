#include <stdio.h>
#include <stdlib.h>
#include "SmartAlloc.h"

#define UINT_SIZE 32
#define CHAR_SIZE 8

typedef unsigned char UChar;
typedef unsigned int UInt;

typedef struct {
UInt packedData;
int bitsUsed;
} BitPacker;

// This function takes a UInt and prints it to screen in capital hex with a comma and space after it.
void CommaDelimit (UInt data) {
   printf("%08X, ", data);
}

// This function takes a UInt and prints it to screen as a unsigned decimal with a bar (|) after it.
void BarDelimit (UInt data) {
   printf("%u|", data);
}

// Same as bpInit from BitPackers Lab
void BpInit (BitPacker *bp) {
   bp->packedData = 0;
   bp->bitsUsed = 0;
}

// Pack |code|. If not enough room, send current packed UInt via |sink| and start a new UInt.
void BpPack (BitPacker *bp, UInt data, void(*print)(UInt)) {
   if(bp->bitsUsed == UINT_SIZE) {
      print(bp->packedData);
      BpInit(bp);
   } 
   bp->packedData <<= CHAR_SIZE; 
   bp->packedData |= data;
   bp->bitsUsed += CHAR_SIZE;
}

// Do any final cleanup needed, assuming no more BpPack calls will occur
void BpStop (BitPacker *bp, void(*print)(UInt)) {
   print(bp->packedData << UINT_SIZE - bp->bitsUsed);
}

int main() {
BitPacker bp1;
BitPacker bp2;
UInt *data;
int count, i;

scanf("%d", &count);
data = calloc(sizeof(UInt), count);
for (i = 0; i < count; i++)
scanf("%x", data + i);

BpInit(&bp1);
BpInit(&bp2);

for (i = 0; i < count; i++)
BpPack(&bp1, data[i], CommaDelimit);
BpStop(&bp1, CommaDelimit);
printf("\n");

for (i = 0; i < count; i++)
BpPack(&bp2, data[i], BarDelimit);
BpStop(&bp2, BarDelimit);
printf("\n");

free(data);
printf("Allocated space: %ld\n", report_space());
return 0;
}
