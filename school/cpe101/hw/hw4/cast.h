#ifndef CAST_H
#define CAST_H

double distance (struct point p1, struct point p2);

int nearest_eye (struct point const input[],struct point eye,int size);

struct color cast_ray (struct ray r,struct sphere spheres[],int 
num_spheres, struct color ambient, struct light l,struct point eye);

void cast_all_rays (double min_x,double max_x,double min_y,double 
max_y,int width,int height,struct point eye,struct sphere spheres[], int 
num_spheres, struct color ambient,struct light l);

int color_scale (double x);

#endif
