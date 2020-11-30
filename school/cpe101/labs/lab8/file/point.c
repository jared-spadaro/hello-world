#include "point.h"

struct point create_point(double x, double y)
{
   struct point p;

   p.x = x;
   p.y = y;

   return p;
}
