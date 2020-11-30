#include <stdio.h>

void setBits (unsigned int *value, int at, int count, unsigned int bitValue) {
   unsigned int mask = 0xFFFFFFFF;
   mask >>= at;
   mask <<= (32 - count);
   mask >>= (32 - at - count);
   //printf("Bitvalue before shift = %X\n", bitValue);
   bitValue <<= at;
   //printf("Bitvalue after shift = %X\n", bitValue);
   *value &= ~mask;
   //printf("Value after AND = %X\n", *value);
   *value |= bitValue;
   //printf("Value after OR = %X\n", *value);
}
