#ifndef FUNCS_STRUCTS_H
#define FUNCS_STRUCTS_H

struct circle grow_circle (struct circle c, double scale);

double distance (struct point p, struct point p2);

int circles_overlap (struct circle c, struct circle c2);

#endif
