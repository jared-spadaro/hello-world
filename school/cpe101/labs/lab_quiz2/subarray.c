#include "subarray.h"

int subarray_min(int const input[],int index1,int index2)
{
   int i;
   int index_smallest=index1;
   
   for(i=index1;i<=index2;i++)
   {
      if(input[i] < input[index_smallest])
      {
         index_smallest = i;
      }
   }
   if(index2<index1)
   {
      return -1;
   }
   return index_smallest;
}

