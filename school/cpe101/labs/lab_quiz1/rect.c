#include "rect.h"

struct point create_point(double x, double y)
{
   struct point p;

   p.x = x;
   p.y = y;

   return p;
}

struct rectangle create_rectangle(struct point top_left,
   struct point bottom_right)
{
   struct rectangle rect;

   rect.top_left = top_left;
   rect.bottom_right = bottom_right;

   return rect;
}
