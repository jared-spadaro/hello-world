#include <float.h>
#include "Problem2.h"

double average (int *input, int size) {
   if(size<=0) return 0;
   int avg = 0;
   double length = size;
   while(size--) {
       avg+=(*input);
       input++;
   }
   double average = avg;
   return average/=length;
}
