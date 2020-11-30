#ifndef PUZZLE_H
#define PUZZLE_H
#include <stdio.h>

struct color {
   double r;
   double g;
   double b;
};

FILE * open_file(char const name[],char const mode[]);

int color_cap (int color_value);

struct color transform_pixel(struct color old_pixel);

void read_and_print (FILE * input,FILE * output);



#endif