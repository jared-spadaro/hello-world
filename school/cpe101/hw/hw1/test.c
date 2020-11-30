#include "data.h"
#include "checkit.h"
#include <stdio.h>

void point_test_cases (void) {
	struct point p = create_point(1.0, 2.0, 3.0);
	struct point p2 = create_point(4.0, 5.0, 6.0);
	checkit_double (p.x, 1.0);
	checkit_double (p.y, 2.0);
	checkit_double (p.z, 3.0);
	checkit_double (p2.x, 4.0);
	checkit_double (p2.y, 5.0);
	checkit_double (p2.z, 6.0);
}

void vector_test_cases (void) {
	struct vector v = create_vector(7.0, 8.0, 9.0);
	struct vector v2 = create_vector(10.0, 11.0, 12.0);
	checkit_double (v.x, 7.0);
	checkit_double (v.y, 8.0);
	checkit_double (v.z, 9.0);
	checkit_double (v2.x, 10.0);
	checkit_double (v2.y, 11.0);
	checkit_double (v2.z, 12.0);
}

void ray_test_cases (void) {
	struct ray r = create_ray (create_point(15.0, 18.0, 19.0), 
	create_vector(24.0, 32.0, 35.0));
	struct ray r2 = create_ray(create_point(12.0, 17.0, 21.0), 
	create_vector(14.0, 11.0, 22.0));
	checkit_double (r.p.x, 15.0);
	checkit_double (r.p.y, 18.0);
	checkit_double (r.p.z, 19.0);
	checkit_double (r.dir.x, 24.0);
	checkit_double (r.dir.y, 32.0);
	checkit_double (r.dir.z, 35.0);
	checkit_double (r2.p.x, 12.0);
	checkit_double (r2.p.y, 17.0);
	checkit_double (r2.p.z, 21.0);
	checkit_double (r2.dir.x, 14.0);
	checkit_double (r2.dir.y, 11.0);
	checkit_double (r2.dir.z, 22.0);
}

void sphere_test_cases (void)
{
	struct sphere s = create_sphere(create_point(42.0, 44.0, 47.0), 
	77.0);
	struct sphere s2 = create_sphere(create_point(56.0, 59.0, 40.0), 
	111.0);
	checkit_double (s.center.x, 42.0);
	checkit_double (s.center.y, 44.0);
	checkit_double (s.center.z, 47.0);
	checkit_double (s.radius, 77.0);
	checkit_double (s2.center.x, 56.0);
	checkit_double (s2.center.y, 59.0);
	checkit_double (s2.center.z, 40.0);
	checkit_double (s2.radius, 111.0);
}
	

int main (void)
{
	point_test_cases();
	vector_test_cases();
	ray_test_cases();
	sphere_test_cases();
	return 0;
}
