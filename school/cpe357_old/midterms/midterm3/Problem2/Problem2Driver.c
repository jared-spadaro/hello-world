#include <stdio.h>
#include "Problem2.h"

int main() {
   unsigned int value, at, count, bitValue;

   /* Read in test values */
   scanf("%x%u%u%x", &value, &at, &count, &bitValue);

   /* Test... */
   setBits(&value, at, count, bitValue);

   /* Print results */
   printf("0x%08X\n", value);
   
   return 0;
}

