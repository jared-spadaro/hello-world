#include "fade.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double distance (struct point p1, struct point p2)
{
   return sqrt((p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y));
}


FILE * open_file(char const name[],char const mode[])
{
   FILE * file = fopen(name,mode);
   if(file == NULL)
   {
      printf("Usage: <input file name> <row> <col> <radius>\n");
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



struct color transform_pixel(struct color old_pixel,double distance,int radius)
{
   struct color new_pixel;
   double fade_scale = (radius - distance) / radius;
   if (fade_scale < 0.2)
   {
      fade_scale = 0.2;
   }
   new_pixel.r = old_pixel.r * fade_scale;
   new_pixel.g = old_pixel.g * fade_scale;
   new_pixel.b = old_pixel.b * fade_scale;
   return new_pixel;   
}


void print_pixels (FILE * input,FILE * output,int width,int height,int row,int col,int radius)
{
   int i,j;
   int r,g,b;
   struct point center = {row,col};
   double pixel_distance;
   struct color new_pixel_color;
   for (i=0;i<height;i++)
   {
      for(j=0;j<width;j++)
      {
	 fscanf(input,"%d %d %d",&r,&g,&b);
         
         struct color old_pixel_color = {r,g,b};
         struct point pixel = {j,i};
	 pixel_distance = distance(pixel,center);
	 new_pixel_color = transform_pixel(old_pixel_color,pixel_distance,radius);
		 
         fprintf(output,"%d\n",color_cap(new_pixel_color.r));
	 fprintf(output,"%d\n",color_cap(new_pixel_color.g));
	 fprintf(output,"%d\n",color_cap(new_pixel_color.b));
      }
   }
}
	     

double convert_double(char const input[],double default_value)
{
   double ret_value;
   int converted;
   converted = sscanf(input,"%lf",&ret_value);
   if(converted == 1)
   {
      return ret_value;
   }
   return default_value;
}



void read_and_print (FILE * input,FILE * output,int row,int col,int radius)
{
   char header[2];
   int width,height;
   int max_color;
   
   
   fscanf(input,"%s",header);
   fscanf(input,"%d %d",&width,&height);
   fscanf(input,"%d",&max_color);
   
   fprintf(output,"%s\n",header);
   fprintf(output,"%d %d\n",width,height);
   fprintf(output,"%d\n",max_color);
   
   print_pixels(input,output,width,height,row,col,radius);
}
   



int main (int argc, char * argv[])
{
   FILE * input = open_file(argv[1],"r");
   FILE * output = open_file("faded.ppm","w");
   read_and_print(input,output,convert_double(argv[2],0),convert_double(argv[3],0),convert_double(argv[4],0));
   return 0;
}


