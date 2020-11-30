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

struct color create_color (double r, double g, double b) {
	struct color c;
	c.r = r;
	c.g = g;
	c.b = b;
	return c;
}

struct light create_light (struct point p,struct color color) {
	struct light l;
	l.p = p;
	l.color = color;
	return l;
}

struct finish create_finish (double ambient,double diffuse,double specular,double roughness) {
	struct finish f;
	f.ambient = ambient;
	f.diffuse = diffuse;
	f.specular = specular;
        f.roughness = roughness;
	return f;
}

struct sphere create_sphere(struct point center, double radius, struct color c, struct finish f) {
	struct sphere sphr;
	sphr.center = center;
	sphr.radius = radius;
	sphr.c = c;
	sphr.f = f;
	return sphr;
}

struct maybe_point create_maybe_point (int isPoint, struct point p) {
	struct maybe_point maybe;
	maybe.isPoint = isPoint;
	maybe.p = p;
	return maybe;
}


