#include "blur.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NUM_ROWS 500
#define NUM_COLS 500





FILE * open_file(char const name[],char const mode[])
{
   FILE * file = fopen(name,mode);
   if(file == NULL)
   {
      printf("Error: invalid file.\n");
      exit(1);
   }
   return file;
}


int square(int x)
{
   return x*x;
}


int color_cap (int color_value)
{
   if(color_value>255)
   {
      color_value = 255;
   }
   return color_value;
}




struct pixel transform_pixel(struct pixel old_pixels[][NUM_COLS],double reach,struct point position)
{
   int i,j;
   struct pixel new_pixel = {0,0,0};
   for(i=-reach;i<reach;i++)
   {
      for(j=-reach;j<reach;j++)
      {
	 if((position.x + j)>0 && (position.y + i)>0)
         {
	    new_pixel.r = new_pixel.r + old_pixels[position.x + j][position.y + i].r;
	    new_pixel.g = new_pixel.g + old_pixels[position.x + j][position.y + i].g;
	    new_pixel.b = new_pixel.b + old_pixels[position.x + j][position.y + i].b;
	 }
      }
   }
   new_pixel.r = new_pixel.r / square(2*reach + 1);
   new_pixel.g = new_pixel.g / square(2*reach + 1);
   new_pixel.b = new_pixel.b / square(2*reach + 1);
   
   return new_pixel;
}
   


void scan_image (struct pixel old_pixels[][NUM_COLS],FILE * input,int width,int height)
{
   int i,j;
   int r,g,b;
   for (i=0;i<height;i++)
   {
      for(j=0;j<width;j++)
      {
         fscanf(input,"%d %d %d",&r,&g,&b);
	 struct pixel old_pixel = {r,g,b};
	 old_pixels[i][j] = old_pixel;
      }
   }
}
	

void transform_and_print (struct pixel old_pixels[][NUM_COLS],FILE * input,FILE * output,int width,int height,double reach)
{
   int i,j;
   struct pixel new_pixel;
   struct pixel new_pixels[NUM_ROWS][NUM_COLS];
   scan_image(old_pixels,input,width,height);
   for (i=0;i<height;i++)
   {
      for(j=0;j<width;j++)
      {
         struct point position = {i,j};
	 new_pixel = transform_pixel(old_pixels,reach,position);
         new_pixels[i][j] = new_pixel;
		 
         fprintf(output,"%d\n",color_cap(new_pixel.r));
         fprintf(output,"%d\n",color_cap(new_pixel.g));
         fprintf(output,"%d\n",color_cap(new_pixel.b));
      }
   }
}
     

double convert_double(char const input[],int default_value)
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




void read_and_print (FILE * input,FILE * output,int cmdline_args,char * cmdline[])
{
   double reach = 4;
   char header[2];
   int width,height;
   int max_color;
   struct pixel old_pixels[NUM_ROWS][NUM_COLS];
  
   if(cmdline_args<=1 || cmdline_args>3)
   {
      printf("Usage: <input file name> <reach value>\n");
	  exit(1);
   }
   
   else if(cmdline_args==3)
   {
      reach = convert_double(cmdline[2],reach);
   }
   
   fscanf(input,"%s",header);
   fscanf(input,"%d %d",&width,&height);
   fscanf(input,"%d",&max_color);
   
   fprintf(output,"%s\n",header);
   fprintf(output,"%d %d\n",width,height);
   fprintf(output,"%d\n",max_color);
   
   transform_and_print(old_pixels,input,output,width,height,reach);
}
   



int main (int argc, char * argv[])
{
   FILE * input = open_file(argv[1],"r");
   FILE * output = open_file("blurred.ppm","w");
   read_and_print(input,output,argc,argv);
   return 0;
}

