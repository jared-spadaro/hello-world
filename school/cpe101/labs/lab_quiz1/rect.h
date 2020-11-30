#ifndef RECT_H
#define RECT_H

struct point
{
   double x;
   double y;
};

struct rectangle
{
   struct point top_left;
   struct point bottom_right;
};

struct point create_point(double x, double y);
struct rectangle create_rectangle(struct point top_left,
   struct point bottom_right);

#endif
