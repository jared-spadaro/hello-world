#include <stdio.h>
#include "Problem1.h"

int main() {
   float a, b, c;

   // Read in values to be ordered...
   scanf("%f%f%f", &a, &b, &c);

   // Call function being tested...
   OrderThree(&a, &b, &c);

   // Print results...
   printf("%.1f %.1f %.1f\n", a, b, c);

   return 0;
}
