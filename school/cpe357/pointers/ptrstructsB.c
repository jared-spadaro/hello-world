#include <stdio.h>

typedef struct {
   int val1;
   int val2;
} Pair;

int Compare (Pair *p1, Pair *p2) {
   int rtn = 1;
   if (p1->val1 < p2->val1) {
      rtn = 0;
   }
   else if (p1->val1 == p2->val1) {
      if (p1->val2 <= p2->val2) {
         rtn = 0;
      }
   }
   else {}
   return rtn;
}

void Swap(Pair *p1, Pair *p2) {
   Pair temp = *p1;
   *p1 = *p2;
   *p2 = temp;
}

int main () {
   Pair vals[100];
   int numVals, ndx;

   scanf("%d", &numVals);
   for (ndx = 0; ndx < numVals; ndx++) 
      scanf("%d %d", &vals[ndx].val1, &vals[ndx].val2);

   //for (ndx = 0; ndx < numVals-1; ndx+=2) 
     // printf("Compare result (%d) = %d\n", ndx, Compare(&vals[ndx], &vals[ndx+1]));

   for (ndx = 0; ndx < numVals; ndx++) 
      printf("(Pair %d) val 1 = %d, val2 = %d\n", ndx, vals[ndx].val1, vals[ndx].val2);
 
   for (ndx = 0; ndx < numVals-1; ndx+=2) 
      Swap(&vals[ndx], &vals[ndx+1]);

   for (ndx = 0; ndx < numVals; ndx++) 
      printf("(Pair %d) val 1 = %d, val2 = %d\n", ndx, vals[ndx].val1, vals[ndx].val2);


   return 0;
}
