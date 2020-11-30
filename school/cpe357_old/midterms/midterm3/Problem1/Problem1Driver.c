/* Test driver for Problem 1.
 */
#include <stdio.h>
#include "Problem1.h"

int main()
{
   unsigned int from, at, count;

   /* Read in test values */
   scanf("%x%u%u", &from, &at, &count);

   /* Test and print results */
   printf("0x%08X\n", getBits(from, at, count));

   return 0;
}

