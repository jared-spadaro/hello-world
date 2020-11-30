#include "data.h"

struct point create_point(double x, double y, double z) {
	struct point p;
	p.x = x;
	p.y = y;
	p.z = z;
	return p;
}

struct vector create_vector(double x, double y, double z) {
	struct vector vec;
	vec.x = x;
	vec.y = y;
	vec.z = z;
	return vec;
}

struct ray create_ray(struct point p, struct vector dir) {
	struct ray ray;
	ray.p = p;
	ray.dir = dir;
	return ray;
}

struct sphere create_sphere(struct point center, double radius) {
	struct sphere sphr;
	sphr.center = center;
	sphr.radius = radius;
	return sphr;
}
