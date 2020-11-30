#include "structs.h"
#include "funcs_structs.h"
#include <stdio.h>
#include "checkit.h"



void point_test_cases(void) 
{
     struct point p = create_point(11.0, 12.0);
     struct point p2 = create_point(15.0, 17.0);
     checkit_double(p.x, 11.0);
     checkit_double(p.y, 12.0);
     checkit_double(p2.x, 15.0);
     checkit_double(p2.y, 17.0);
}

void circle_test_cases(void)
{  
     struct circle c = create_circle (create_point(5.0, 6.0), 3.0);
     struct circle c2 = create_circle (create_point(2.0, 1.0), 9.0);
     checkit_double(c.center.x, 5.0);
     checkit_double(c.center.y, 6.0);
     checkit_double(c.radius, 3.0);
     checkit_double(c2.center.x, 2.0);
     checkit_double(c2.center.y, 1.0);
     checkit_double(c2.radius, 9.0);
}

void grow_circle_test_cases (void)
{	
	struct circle c=grow_circle(create_circle(create_point(1.0, 		2.0),3.0), 4.0);
	struct circle c2=grow_circle(create_circle(create_point(5.0, 		6.0),7.0), 8.0);	

 	
	checkit_double(c.center.x, 1.0);
	checkit_double(c.center.y, 2.0);
	checkit_double(c.radius, 12.0);
	checkit_double(c2.center.x, 5.0);
	checkit_double(c2.center.y, 6.0);
	checkit_double(c2.radius, 56.0);
}

void distance_test_cases (void)
{
	double dist=distance(create_point(1.0,2.0),create_point(3.0,4.0));
	double dist2=distance(create_point(5.0,6.0),create_point(7.0,9.0));
	checkit_double(dist, 2.828427);
	checkit_double(dist2, 3.605551);
	
}

void circles_overlap_test_cases(void)
{
	struct circle c = create_circle(create_point(1.0,2.0),3.0);
	struct circle c2 = create_circle(create_point(4.0,5.0),6.0);
	struct circle c3 = create_circle(create_point(17.0, 31.0),8.0);
	struct circle c4 = create_circle(create_point(-18.0, -21.0),12.0);
	int overlap = circles_overlap(c,c2);
	int overlap2 = circles_overlap(c3,c4);
	checkit_int(overlap, 1);
	checkit_int(overlap2, 0);
}	

int main(int argc, char **argv)
{
   point_test_cases();
   circle_test_cases();
   grow_circle_test_cases();
   distance_test_cases();
   circles_overlap_test_cases();
   return 0;
}
