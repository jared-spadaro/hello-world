#include "count.h"

int count_value(int const input[],int length,int value)
{
   int i;
   int count=0;
   for(i=0;i<length;i++)
   {
      if(input[i] == value)
      {
         count++;
      }
   }
   return count;
}


