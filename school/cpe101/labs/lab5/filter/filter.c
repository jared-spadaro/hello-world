#include "point.h"
#include "filter.h"

int are_positive (double const input[],int size,double result[])
{
   int i;
   int next_index=0;
   for(i=0;i<size;i++)
   {
      if(input[i]>0)
      {
         result[next_index]=input[i];
         next_index++;
      }
   }
   return next_index;
}

int are_greater_than(double n,double const input[],int size,double 
result[])
{
   int i;
   int next_index=0;
   for(i=0;i<size;i++)
   {
      if(input[i]>n)
     {
        result[next_index]=input[i];
        next_index++;
     }
   }
   return next_index;
}

int are_in_first_quadrant(struct point const input[],int size,struct 
point result[])
{
   int i;
   int next_index=0;
   for(i=0;i<size;i++)
   {
      if(input[i].x>0 && input[i].y>0)
      {
         result[next_index] = input[i];
         next_index++;
      }
   }
   return next_index;
}  
