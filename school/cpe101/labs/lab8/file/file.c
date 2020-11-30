#include "point.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>






      

   


int main(int argc, char*argv[])
{
   double x;
   double y;
   int result;
   FILE *file;
   struct point p;
   
   file = fopen(argv[1],"r");
   
   if(argc<=1)
   {
      printf("Error.\n");
      exit(1);
   }
   while(result!=EOF)
   {
      result=fscanf(file,"%lf %lf",&x,&y);
      
      p=create_point(x,y);
      if(p.x>0&&p.y>0)
      {
         printf("POINT x: %f y: %f\n",x,y);
      }
   }
 
   
   
   
  
   return 0;
}
