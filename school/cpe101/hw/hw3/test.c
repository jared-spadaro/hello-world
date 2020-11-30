#include "data.h"
#include "vector_math.h"
#include "collisions.h"
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
	struct ray r1 = create_ray (create_point(15.0, 18.0, 19.0), 
	create_vector(24.0, 32.0, 35.0));
	struct ray r2 = create_ray(create_point(12.0, 17.0, 21.0), 
	create_vector(14.0, 11.0, 22.0));
	checkit_double (r1.p.x, 15.0);
	checkit_double (r1.p.y, 18.0);
	checkit_double (r1.p.z, 19.0);
	checkit_double (r1.dir.x, 24.0);
	checkit_double (r1.dir.y, 32.0);
	checkit_double (r1.dir.z, 35.0);
	checkit_double (r2.p.x, 12.0);
	checkit_double (r2.p.y, 17.0);
	checkit_double (r2.p.z, 21.0);
	checkit_double (r2.dir.x, 14.0);
	checkit_double (r2.dir.y, 11.0);
	checkit_double (r2.dir.z, 22.0);
}

void sphere_test_cases (void)
{
	struct sphere s1 = create_sphere(create_point(42.0, 44.0, 47.0), 
	77.0);
	struct sphere s2 = create_sphere(create_point(56.0, 59.0, 40.0), 
	111.0);
	checkit_double (s1.center.x, 42.0);
	checkit_double (s1.center.y, 44.0);
	checkit_double (s1.center.z, 47.0);
	checkit_double (s1.radius, 77.0);
	checkit_double (s2.center.x, 56.0);
	checkit_double (s2.center.y, 59.0);
	checkit_double (s2.center.z, 40.0);
	checkit_double (s2.radius, 111.0);
}
	
void scale_vector_test_cases (void)
{
   struct vector v1 = create_vector(2.0, 1.0, 4.0);
   struct vector v2 = create_vector(12.0, 3.0, 8.0);
   struct vector new_v1 = scale_vector(v1, 1.5);
   struct vector new_v2 = scale_vector(v2, 5.0);
   checkit_double(new_v1.x,3.0);
   checkit_double(new_v1.y,1.5);
   checkit_double(new_v1.z,6.0);
   checkit_double(new_v2.x,60.0);
   checkit_double(new_v2.y,15.0);
   checkit_double(new_v2.z,40.0);
}

void dot_vector_test_cases (void)
{
   struct vector v1 = create_vector(4.0, 2.0, 7.0);
   struct vector v2 = create_vector(3.0, 9.0, 5.0);
   struct vector v3 = create_vector(11.0, 14.0, 2.0);
   struct vector v4 = create_vector(8.0, 10.0, 6.0);
   double dot_product1 = dot_vector(v1, v2);
   double dot_product2 = dot_vector(v3, v4);

   checkit_double(dot_product1,65.0);
   checkit_double(dot_product2,240.0);
}

void length_vector_test_cases (void)
{
   struct vector v1 = create_vector(3.0, 7.0, 5.0);
   struct vector v2 = create_vector(21.0, 34.0, 56.0);
   double length1 = length_vector(v1);
   double length2 = length_vector(v2);
   checkit_double(length1,9.110433);
   checkit_double(length2,68.796802);
}

void normalize_vector_test_cases (void)
{
   struct vector v1 = create_vector(2.0, 5.0, 3.0);
   struct vector v2 = create_vector(56.0, 47.0, 25.0);
   struct vector normal_v1 = normalize_vector(v1);
   struct vector normal_v2 = normalize_vector(v2);
   double new_length1 = length_vector(normal_v1);
   double new_length2 = length_vector(normal_v2);
 
   checkit_double(new_length1,1.0);
   checkit_double(normal_v1.x,0.324443);
   checkit_double(normal_v1.y,0.811107);
   checkit_double(normal_v1.z,0.486664);
   checkit_double(new_length2,1.0);
   checkit_double(normal_v2.x,0.724771);
   checkit_double(normal_v2.y,0.608290);
   checkit_double(normal_v2.z,0.323559);

}

void difference_point_test_cases (void)
{
   struct point p1 = create_point(7.0,3.0,5.0);
   struct point p2 = create_point(6.0,11.0,2.0);
   struct point p3 = create_point(34.0, 27.0,51.0);
   struct point p4 = create_point(17.0,21.0,33.0);
   struct vector v1 = difference_point(p1,p2);
   struct vector v2 = difference_point(p3,p4);
   
   checkit_double(v1.x,1.0);
   checkit_double(v1.y,-8.0);
   checkit_double(v1.z,3.0);
   checkit_double(v2.x,17.0);
   checkit_double(v2.y,6.0);
   checkit_double(v2.z,18.0);
}

void difference_vector_test_cases (void)
{
   struct vector v1 = create_vector(22.0,15.0,20.0);
   struct vector v2 = create_vector(6.0,4.0,8.0);
   struct vector v3 = create_vector(2.0,12.0,7.0);
   struct vector v4 = create_vector(64.0,37.0,23.0);
   struct vector difference1 = difference_vector(v1,v2);
   struct vector difference2 = difference_vector(v3,v4);
   
   checkit_double(difference1.x,16.0);
   checkit_double(difference1.y,11.0);
   checkit_double(difference1.z,12.0);
   checkit_double(difference2.x,-62.0);
   checkit_double(difference2.y,-25.0);
   checkit_double(difference2.z,-16.0);
}

void translate_point_test_cases (void)
{
   struct point p1 = create_point(2.0,5.0,6.0);
   struct point p2 = create_point(-56.0,-24.0,-87.0);
   struct vector v1 = create_vector(7.0,3.0,1.0);
   struct vector v2 = create_vector(19.0,14.0,45.0);
   struct point new_point1 = translate_point(p1,v1);
   struct point new_point2 = translate_point(p2,v2);
   
   checkit_double(new_point1.x,9.0);
   checkit_double(new_point1.y,8.0);
   checkit_double(new_point1.z,7.0);
   checkit_double(new_point2.x,-37.0);
   checkit_double(new_point2.y,-10.0);
   checkit_double(new_point2.z,-42.0);
}

void sphere_intersection_point_test_cases (void)
{
   struct point ray_origin_1 = create_point(0,0,0);
   struct point ray_origin_2 = create_point(8,0,0);
   struct point ray_origin_3 = create_point(6,0,0);
   struct point ray_origin_4 = create_point(0,0,0);
   struct vector ray_dir_1 = create_vector(17,0,0);
   struct vector ray_dir_2 = create_vector(-34,0,0);
   struct vector ray_dir_3 = create_vector(42,0,0);
   struct vector ray_dir_4 = create_vector(85,72,0);
   
   struct ray  test_ray_1 = create_ray(ray_origin_1,ray_dir_1);
   struct ray  test_ray_2 = create_ray(ray_origin_2,ray_dir_2);
   struct ray  test_ray_3 = create_ray(ray_origin_3,ray_dir_3);
   struct ray  test_ray_4 = create_ray(ray_origin_4,ray_dir_4);
   
   struct point sphere_center_1 = create_point(8,0,0);
   struct point sphere_center_2 = create_point(-12,-7,0);
   struct point sphere_center_3 = create_point(0,0,0);
   struct point sphere_center_4 = create_point(50,50,0);
   double sphere_radius_1 = 3;
   double sphere_radius_2 = 7;
   double sphere_radius_3 = 5;
   double sphere_radius_4 = 14;
   
   struct sphere test_sphere_1 = create_sphere(sphere_center_1,sphere_radius_1);
   struct sphere test_sphere_2 = create_sphere(sphere_center_2,sphere_radius_2);
   struct sphere test_sphere_3 = create_sphere(sphere_center_3,sphere_radius_3);
   struct sphere test_sphere_4 = create_sphere(sphere_center_4,sphere_radius_4);

   struct maybe_point intersect_point_1 = sphere_intersection_point (test_ray_1,test_sphere_1);
   struct maybe_point intersect_point_2 = sphere_intersection_point (test_ray_2,test_sphere_2);
   struct maybe_point intersect_point_3 = sphere_intersection_point (test_ray_3,test_sphere_3);
   struct maybe_point intersect_point_4 = sphere_intersection_point (test_ray_4,test_sphere_4); 
 
   checkit_double (intersect_point_1.isPoint,1);
   checkit_double (intersect_point_1.p.x,5);
   checkit_double (intersect_point_1.p.y,0);
   checkit_double (intersect_point_1.p.z,0);

   checkit_double (intersect_point_2.isPoint,1);
   checkit_double (intersect_point_2.p.x,-12);
   checkit_double (intersect_point_2.p.y,0);
   checkit_double (intersect_point_2.p.z,0);

   checkit_double (intersect_point_3.isPoint,0);
   checkit_double (intersect_point_3.p.x,0);
   checkit_double (intersect_point_3.p.y,0);
   checkit_double (intersect_point_3.p.z,0);

   checkit_double (intersect_point_4.isPoint,1);
   checkit_double (intersect_point_4.p.x,44.060905);
   checkit_double (intersect_point_4.p.y,37.322179);
   checkit_double (intersect_point_4.p.z,0);
}

void find_intersection_points_test_cases_1(void)
{
   
   int num_spheres = 3;
   struct sphere spheres[3];
   spheres[0] = create_sphere(create_point(12,0,0),2);
   spheres[1] = create_sphere(create_point(8,0,0),3);
   spheres[2] = create_sphere(create_point(-12,0,0),5);
   struct ray r = create_ray(create_point(0,0,0),create_vector(20,0,0));
   struct sphere hit_spheres[2];
   struct point intersection_points[2];
   

   int number_spheres_hit = find_intersection_points(spheres,num_spheres,r,hit_spheres,intersection_points);

   checkit_double(hit_spheres[0].center.x,12);
   checkit_double(hit_spheres[0].center.y,0);
   checkit_double(hit_spheres[0].center.z,0);
   checkit_double(hit_spheres[0].radius,2);
   checkit_double(hit_spheres[1].center.x,8);
   checkit_double(hit_spheres[1].center.y,0);
   checkit_double(hit_spheres[1].center.z,0);
   checkit_double(hit_spheres[1].radius,3);
   checkit_double(intersection_points[0].x,10);
   checkit_double(intersection_points[0].y,0);
   checkit_double(intersection_points[0].z,0);
   checkit_double(intersection_points[1].x,5);
   checkit_double(intersection_points[1].y,0);
   checkit_double(intersection_points[1].z,0);
   checkit_double(number_spheres_hit,2);
   
}

void find_intersection_points_test_cases_2(void)
{
   int num_spheres = 4;
   struct sphere spheres [4];
   spheres[0] = create_sphere(create_point(27,20,0),10);
   spheres[1] = create_sphere(create_point(20,-12,0),5);
   spheres[2] = create_sphere(create_point(9,10,0),8);
   spheres[3] = create_sphere(create_point(-45,-65,0),0);
   struct ray r = create_ray(create_point(0,0,0),create_vector(100,100,0));
   struct sphere hit_spheres[2];
   struct point intersection_points[2];
   int number_spheres_hit = find_intersection_points(spheres,num_spheres,r,hit_spheres,intersection_points);

   checkit_double(hit_spheres[0].center.x,27);
   checkit_double(hit_spheres[0].center.y,20);
   checkit_double(hit_spheres[0].center.z,0);
   checkit_double(hit_spheres[0].radius,10);
   checkit_double(hit_spheres[1].center.x,9);
   checkit_double(hit_spheres[1].center.y,10);
   checkit_double(hit_spheres[1].center.z,0);
   checkit_double(hit_spheres[1].radius,8);
   checkit_double(intersection_points[0].x,17.355897);
   checkit_double(intersection_points[0].y,17.355897);
   checkit_double(intersection_points[0].z,0);
   checkit_double(intersection_points[1].x,3.865286);
   checkit_double(intersection_points[1].y,3.865286);
   checkit_double(intersection_points[1].z,0);
   checkit_double(number_spheres_hit,2);
   
}

void sphere_normal_at_point_test_cases(void)
{
   struct sphere test_sphere_1 = create_sphere(create_point(47,0,0),15);
   struct sphere test_sphere_2 = create_sphere(create_point(0,-27,0),4);
   struct point test_point_1 = create_point(32,0,0);
   struct point test_point_2 = create_point(0,-23,0);
   struct vector test_vector_1 = sphere_normal_at_point(test_sphere_1,test_point_1);
   struct vector test_vector_2 = sphere_normal_at_point(test_sphere_2,test_point_2);
  
   checkit_double(test_vector_1.x,-1);
   checkit_double(test_vector_1.y,0);
   checkit_double(test_vector_1.z,0);

   checkit_double(test_vector_2.x,0);
   checkit_double(test_vector_2.y,1);
   checkit_double(test_vector_2.z,0);
}

int main (void)
{
	point_test_cases();
	vector_test_cases();
	ray_test_cases();
	sphere_test_cases();
	scale_vector_test_cases();
	dot_vector_test_cases();
	length_vector_test_cases();
	normalize_vector_test_cases();
	difference_point_test_cases();
	difference_vector_test_cases();
	translate_point_test_cases();
	sphere_intersection_point_test_cases();
	find_intersection_points_test_cases_1();
	find_intersection_points_test_cases_2();
	sphere_normal_at_point_test_cases();
	return 0;
}
