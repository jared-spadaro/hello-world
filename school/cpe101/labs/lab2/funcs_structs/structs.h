#ifndef STRUCTS_H
#define STRUCTS_H

struct point {
	double x;
	double y;
};

struct point create_point (double x, double y);

struct circle {
	struct point center;
	double radius;
};

struct circle create_circle (struct point center, double radius);

#endif
