#include "structs.h"
#include "funcs_structs.h"
#include <math.h>

struct circle grow_circle (struct circle c, double scale) {
	return create_circle(c.center, c.radius * scale);
}

double distance (struct point p, struct point p2) {
	double dist;	
	dist = sqrt(((p.x-p2.x)*(p.x-p2.x)) + ((p.y-p2.y)*(p.y-p2.y)));
	return dist;
	
}

int circles_overlap (struct circle c, struct circle c2)
{
	return distance(c.center, c2.center) < (c.radius + c2.radius);
}




	
 
