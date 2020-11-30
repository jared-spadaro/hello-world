#include "conditional.h"

double min (double x, double y)
{
   if(x<y)
   {
      return x;
   }
   else
   {
      return y;
   }
}

double max (double x, double y)
{
   if(x>y)
   {
      return x;
   }
   else
   {
      return y;
   }
}

double max_of_three (double x, double y, double z)
{
   if(x>y)
   {
      if(x>z)
      {
         return x;
      }
      else
      {
         return z;
      }
   }
   else if(y>z)
      {
         return y;
      }
   else
   {
      return z;
   }
}

int rental_late_fee (int x)
{
   int late_fee;
   if(x<=0)
   {
      late_fee=0;
   }
   else if(x>0 && x<=9)
   {
      late_fee=5;
   }
   else if(x>9 && x<=15)
   {
      late_fee=7;
   }
   else if(x>15 && x<=24)
   {
      late_fee=19;
   }
   else if(x>24)
   {
      late_fee=100;
   }
   return late_fee;
}

