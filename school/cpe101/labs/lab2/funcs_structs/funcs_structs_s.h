#ifndef FUNCS_STRUCTS_S_H
#define FUNCS_STRUCTS_S_H

struct point {
   double x;
   double y;
};

struct point create_point (double x,double y);

struct circle {
   struct point p;
   double radius;
};

struct circle create_circle (struct point p, double radius);

struct circle grow_circle(struct circle c, double scale);

double distance(struct point p1, struct point p2);

int circle_overlap(struct circle c1,struct circle c2);


#endif
