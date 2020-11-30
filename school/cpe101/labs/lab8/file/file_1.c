#include "point.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE * open_file(char const name[])
{
   FILE * file = fopen(name,"r");
   if(file==NULL)
   {
      printf("Error.\n");
      exit(1);
   }
   return file;
}

void read_and_print (FILE *file,int cmd_arg)
{
   double x;
   double y;
   int result;
   struct point p;
   if(cmd_arg<=1)
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
         printf("POINT: x %f y: %f\n",x,y);
      }
   }
}
      

   


int main(int argc, char*argv[])
{
   FILE * file = open_file(argv[1]);
   read_and_print(file,argc);
 
   
   
   
  
   return 0;
}
