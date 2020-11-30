#include <stdio.h>
#include <stdlib.h>

void swapbytes () {
   unsigned short s;
   printf("Enter short value (in hex): ");
   scanf("%X",&s);
   unsigned mask = s << 8;
   s = mask | s >> 8;
   printf("Swapped short value = %X\n", s);
}

int main (void) {
   swapbytes();
   return 0;
}
   
