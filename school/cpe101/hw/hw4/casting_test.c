#include "data.h"
#include "vector_math.h"
#include "collisions.h"
#include "cast.h"
#include <stdio.h>

void casting_test ()
{
   struct point eye = create_point(0,0,-14.0);
   struct sphere spheres[2];
   spheres[0] = create_sphere(create_point(1.0,1.0,0),2.0,create_color(0,0,1.0),create_finish(0.2,0.4,0.5,0.05));
   spheres[1] = 
   create_sphere(create_point(0.5,1.5,-3.0),0.5,create_color(1.0,0,0),create_finish(0.4,0.4,0.5,0.05));
   int num_spheres = 2;
   double min_x = -10;
   double max_x = 10;
   double min_y = -7.5;
   double max_y = 7.5;
   int width = 1024;
   int height = 768;
   struct color ambient = create_color(1.0,1.0,1.0);
   struct light l = create_light(create_point(-100,100,-100),create_color(1.5,1.5,1.5));
   
   cast_all_rays(min_x,max_x,min_y,max_y,width,height,eye,spheres,num_spheres,ambient,l);
}









int main (void)
{
   casting_test();
   return 0;
}
