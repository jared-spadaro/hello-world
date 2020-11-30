#include <stdio.h>
#include <limits.h>
#include <strings.h>\

int main (void) {
   double d;
   float f;
   int i;
   scanf("%*[^0-9]%d",&i);
   printf("The number read was: %d\n", i);
   //printf("Floating point value: %g\nDouble value: %le\n", f,d);
   return 0;
}
