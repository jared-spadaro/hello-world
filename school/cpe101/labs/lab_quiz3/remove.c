#include "remove.h"

void remove_index(int input[],int length,int index)
{
   int i;
   if(index>0 && index<length)
   {
      for(i=0;i<length-index;i++)
      {
         input[index+i] = input[index+(i+1)];
      }
   }
}
