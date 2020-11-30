#include <stdio.h>

#define MAX 100

void AddToSort(int *vals, int endNdx, int toInsert) {
   int *next = vals + 1, *loc = vals + endNdx, *pLoc = vals + endNdx -1;
   //my code start
   while (toInsert < *pLoc && loc > vals) {
      *loc-- = *pLoc--;
   }
   *loc = toInsert;
   //my code end
}

int main() {
   int vals[MAX], numVals, ndx, toInsert;

   scanf("%d", &numVals);
   for (ndx = 0; ndx < numVals; ndx++) {
      scanf("%d", &vals[ndx]);
   }

   scanf("%d", &toInsert);

   AddToSort(vals, numVals, toInsert);
 
   for (ndx = 0; ndx < numVals + 1; ndx++) {
      printf("%d ", vals[ndx]);
   }
   printf("\n");

   return 0;
}

