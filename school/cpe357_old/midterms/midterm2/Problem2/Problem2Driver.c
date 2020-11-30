#include <stdio.h>
#include <float.h>
#include "Problem2.h"

#define MAX_SIZE 100

int main() {
   int size, ndx, values[MAX_SIZE];
   double avg = DBL_MIN;

   /* Read in values to average */
   scanf("%d", &size);

   for (ndx = 0; ndx < size; ndx++)
      scanf("%d", &values[ndx]);

   /* Call function being tested */
   avg = average(values, size);

   /* Print results */
   printf("%.2f\n", avg);

   return 0;
}
