#include "subarray.h"
#include "checkit.h"
#include <stdio.h>

void subarray_min_test_cases()
{
   int input[7] = {5,2,7,1,3,12,10};
   int input_A[10] = {76,23,97,7,5,85,3,8,45,87};
   
   int index1 = 1;
   int index1_A = 2;
   
   int index2 = 5;
   int index2_A = 5;
   
   int index_smallest = subarray_min(input,index1,index2);
   int index_smallest_A = subarray_min(input_A,index1_A,index2_A);
   int index_smallest_B = subarray_min(input,index2,index1);
   
   checkit_int(index_smallest,3);
   checkit_int(index_smallest_A,4);
   checkit_int(index_smallest_B,-1);
}





int main (void)
{
   subarray_min_test_cases();
   return 0;
}
