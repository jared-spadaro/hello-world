#include "puzzle.h"
#include <stdio.h>
#include <stdlib.h>

FILE * open_file(char const name[],char const mode[])
{
   FILE * file = fopen(name,mode);
   if(file == NULL)
   {
      printf("Usage: <input file name>\n");
      exit(1);
   }
   return file;
}


int color_cap (int color_value)
{
   if(color_value>255)
   {
      color_value = 255;
   }
   return color_value;
}


struct color transform_pixel(struct color old_pixel)
{
   struct color new_pixel;
   new_pixel.r = old_pixel.r * 10;
   new_pixel.g = new_pixel.r;
   new_pixel.b = new_pixel.r;
   return new_pixel;
}


void read_and_print (FILE * input,FILE * output)
{
   char header[2];
   int width,height;
   int max_color;
   int r,g,b;
   int result;
   
   fscanf(input,"%s",header);
   fscanf(input,"%d %d",&width,&height);
   fscanf(input,"%d",&max_color);
   
   fprintf(output,"%s\n",header);
   fprintf(output,"%d %d\n",width,height);
   fprintf(output,"%d\n",max_color);
   
   while(result!=EOF)
   {
      result = fscanf(input, "%d %d %d",&r,&g,&b);
	  
      struct color old_pixel = {r,g,b};
      struct color new_pixel = transform_pixel(old_pixel);
	  
      fprintf(output,"%d\n",color_cap(new_pixel.r));
      fprintf(output,"%d\n",color_cap(new_pixel.g));
      fprintf(output,"%d\n",color_cap(new_pixel.b));
   }
}
   



int main (int argc, char * argv[])
{
   FILE * input = open_file(argv[1],"r");
   FILE * output = open_file("hidden.ppm","w");
   read_and_print(input,output);
   fclose(input);
   fclose(output);
   return 0;
}










