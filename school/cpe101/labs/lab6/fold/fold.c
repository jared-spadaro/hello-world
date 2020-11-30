#include "point.h"
#include "fold.h"
#include <math.h>

double sum(double const input[],int size)
{
   int i;
   double sum_of = 0;
   for(i=0;i<size;i++)
   {
      sum_of = sum_of + input[i];
   }
   return sum_of;
}

int index_of_smallest(double const input[],int size)
{
   int i;
   int mindex = 0;
   for(i=0;i<size;i++)
   {
      if(input[mindex] > input[i])
      {   
         mindex = i;
      }
   }
   if(size<=0)
   {
      mindex = -1;
   }
   return mindex;
}

double distance (struct point p1, struct point p2)
{
   return sqrt ((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
}

int nearest_origin(struct point const input[],int size)
{
   int i;
   int index_nearest=0;
   struct point origin = create_point(0,0);
   for(i=0;i<size;i++)
   {
      if (distance(input[index_nearest],origin) > distance(input[i],origin))
      {
         index_nearest = i;
      }
   }
   if(size<=0)
   {
      return -1;
   }
   return index_nearest;
}       

