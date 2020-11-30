#include "rect.h"
#include "rect_funcs.h"

double rectangle_area (struct rectangle rec)
{
   double area;
   double disty;
   double distx;
   disty = rec.top_left.y - bottom_right.y;
   distx = rec.bottom_right.x - top_left.x;;
   area = disty * distx;
   return area;
}
