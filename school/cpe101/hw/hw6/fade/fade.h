#ifndef FADE_H
#define FADE_H
#include <stdio.h>

struct color {
   int r;
   int g;
   int b;
};

struct point {
   double x;
   double y;
};

double distance (struct point p1, struct point p2);

FILE * open_file(char const name[],char const mode[]);

int color_cap (int color_value);

struct color transform_pixel(struct color old_pixel,double distance,int radius);

void print_pixels (FILE * input,FILE * output,int width,int height,int row,int col,int radius);

double convert_double(char const input[],double default_value);

void read_and_print (FILE * input,FILE * output,int row,int col,int radius);



#endif