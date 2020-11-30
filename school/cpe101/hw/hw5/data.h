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




struct color create_color (double r, double g, double b);

struct color {
	double r;
	double g;
	double b;
};

struct light {
	struct point p;
	struct color color;
};

struct light create_light (struct point p, struct color color);

struct finish {
	double ambient;
	double diffuse;
        double specular;
        double roughness;
};

struct finish create_finish(double ambient,double diffuse,double specular,double roughness);

struct sphere {
	struct point center;
	double radius;
	struct color c;
	struct finish f;
};


struct sphere create_sphere(struct point center, double radius, struct color c, struct finish f);

struct maybe_point {
	int isPoint;
	struct point p;
};

struct maybe_point create_maybe_point (int isPoint, struct point p);





#endif
