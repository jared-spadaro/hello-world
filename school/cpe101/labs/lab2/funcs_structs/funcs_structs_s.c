#include "funcs_structs_s.h"
#include <math.h>

struct point create_point (double x, double y)
{
   struct point p;
   p.x = x;
   p.y = y;
   return p;
}

struct circle create_circle (struct point p, double radius)
{
   struct circle c;
   c.p = p;
   c.radius = radius;
   return c;
}

struct circle grow_circle (struct circle c, double scale)
{
   return create_circle (c.p,c.radius*scale);
}

double distance (struct point p1, struct point p2)
{
   return sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

int circle_overlap (struct circle c1, struct circle c2)
{
   return distance(c1.p,c2.p)<(c1.radius+c2.radius);
}