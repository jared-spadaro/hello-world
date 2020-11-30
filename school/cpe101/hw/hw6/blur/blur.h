#ifndef BLUR_H
#define BLUR_H
#include <stdio.h>
#define NUM_COLS 500

struct pixel {
   int r;
   int g;
   int b;
};

struct point {
   int x;
   int y;
};

FILE * open_file(char const name[],char const mode[]);

int square(int x);

int color_cap (int color_value);

struct pixel transform_pixel(struct pixel old_pixels[][NUM_COLS],double reach,struct point position);

void scan_image (struct pixel old_pixels[][NUM_COLS],FILE * input,int width,int height);

void transform_and_print (struct pixel old_pixels[][NUM_COLS],FILE * input,FILE * output,int width,int height,double reach);

double convert_double(char const input[],int default_value);

void read_and_print (FILE * input,FILE * output,int cmdline_args,char * cmdline[]);




#endif