#include "funcs_structs_s.h"
#include <math.h>
#include <stdio.h>
#include "checkit.h"

void grow_circle_test_cases()
{
   struct circle c = create_circle(create_point(1,2),4);
   double scale = 2;
   struct circle new_c = grow_circle(c,scale);
   checkit_double(new_c.p.x,1);
   checkit_double(new_c.p.y,2);
   checkit_double(new_c.radius,8);
}

void distance_test_cases()
{
   struct point p1 = create_point(2,4);
   struct point p2 = create_point(3,5);
   double dist = distance(p1,p2);
   checkit_double(dist,1.414213);
}

void circles_overlap_test_cases()
{
   struct circle c1 = create_circle(create_point(2,4),5);
   struct circle c2 = create_circle(create_point(4,6),4);
   struct circle c3 = create_circle(create_point(-2,-5),2);
   struct circle c4 = create_circle(create_point(5,6),7);
   int is_overlap = circle_overlap(c1,c2);
   int is_overlap_1 = circle_overlap(c3,c4);
   checkit_int(is_overlap,1);
   checkit_int(is_overlap_1,0);
}

int main (void)
{
   grow_circle_test_cases();
   distance_test_cases();
   circles_overlap_test_cases();
   return 0;
}


