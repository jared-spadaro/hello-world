#ifndef DATA_H
#define DATA_H

struct point {
	double x;
	double y;
	double z;
};

struct point create_point(double x, double y, double z);



struct vector {
	double x;
	double y;
	double z;
};

struct vector create_vector(double x, double y, double z);



struct ray {
	struct point p;
	struct vector dir;
};

struct ray create_ray(struct point p, struct vector dir);



struct sphere {
	struct point center;
	double radius;
};

struct sphere create_sphere(struct point center, double radius);



#endif
