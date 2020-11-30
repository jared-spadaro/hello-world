#include <stdio.h>
#include "Problem4.h"

#define MAX_SIZE 100

int main() {
   int ndx, aSize, bSize, a[MAX_SIZE], b[MAX_SIZE], *result;
   int space, expectedSpace;
  
   /* Read in first array */
   scanf("%d", &aSize);

   for (ndx = 0; ndx < aSize; ndx++)
      scanf("%d", &a[ndx]);
   
   /* Read in second array */
   scanf("%d", &bSize);

   for (ndx = 0; ndx < bSize; ndx++)
      scanf("%d", &b[ndx]);

   /* Read in expected memory use */
   scanf("%d", &expectedSpace);

   /* Call the function being tested */
   result = mergeArrays(a, aSize, b, bSize);

   /* Print results */
   for (ndx = 0; ndx < aSize + bSize; ndx++)
      printf("%d ", result[ndx]);

   printf("\n");

   /* Check memory use */
   space = report_space();

   if (space > expectedSpace)
      printf("Too much memory allocated\n");
   else if (space < expectedSpace)
      printf("Too little memory allocated\n");

   free(result);

   if (report_space())
      printf("Unexpected space used after free\n");

   return 0;
}
