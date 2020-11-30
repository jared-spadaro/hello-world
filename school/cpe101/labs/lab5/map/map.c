#include "point.h"
#include "map.h"
#include <math.h>

void square_all (double const input [], int size, double result[])
{
   int i;
   for (i=0; i<size; i++)
   {
      result[i] = input[i] * input[i];
   }
}

void add_n_all (double n,double const input[],int size,double result[])
{
   int i;
   for (i=0; i<size; i++)
   {
      result[i] = input[i] + n;
   }
}

double distance (struct point p1, struct point p2)
{
   return sqrt(((p1.x-p2.x)*(p1.x-p2.x)) + ((p1.y-p2.y)*(p1.y-p2.y)));
} 

void distance_all(struct point const input[],int size,double result[])
{
   int i;
   struct point p = {0,0};
   for(i=0;i<size;i++)
   {
      result[i] = distance(p,input[i]);
   }
}
