#include <stdio.h>
#include <stdlib.h>

void read_example ()
{
   int x;
   int y;
   double a;
   double b;
   
   int result = scanf("%d %d", &x,&y);
   
   if(result==2)
   {
      if(x>y)
      {
         printf("Larger = %d\n",x);
      }
      else
      {
         printf("Larger = %d\n",y);
      }
   
      scanf("%lf %lf", &a,&b);
   
      if(a>b)
      {
         printf("Larger = %lf\n",a);
      }
      else
      {
         printf("Larger = %lf\n",b);
      }
   }
   else
      {
        printf("Invalid input");
      }
}



int main (void)
{
   read_example();
   return 0;
}



