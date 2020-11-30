#include "rect.h"
#include "rect_funcs.h"
#include "checkit.h"

void rectangle_area_test_cases (void)
{
   struct point topleft1 = create_point (0,17.0);
   struct point bottomright1 = create_point (12.0,0);
   struct point topleft2 = create_point (0,42.87);
   struct point bottomright2 = create_point (57.83,0);
   struct rectangle rec1 = create_rectangle(topleft1,bottomright1);
   struct rectangle rec2 = create_rectangle(topleft2,bottomright2);
   double area1 = rectangle_area(rec1);
   double area2 = rectangle_area(rec2);
   checkit_double (area1,204.0);
   checkit_double (area2,2479.1721);
}










int main (void)
{
   rectangle_area_test_cases();
   return 0;
}
