#include "structs.h"
#include "funcs_structs.h"

struct point create_point (double x, double y) {
	struct point p;
	p.x = x;
	p.y = y;
	return p;
}

struct circle create_circle (struct point center, double radius) {	
	struct circle c;
	c.center = center;
	c.radius = radius;
	return c;
}
