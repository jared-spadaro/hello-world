#include "while.h"

void for_version(int result[], int size)
{
   int i;
   for (i = 0; i < size; i++)
   {
      result[i] = i;
   }
}

void while_version(int result[], int size)
{
   int i=0;
   while(i<size)
   {
   result[i] = i;
   i++;
   }
}
