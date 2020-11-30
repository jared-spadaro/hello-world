#include "data.h"
#include "vector_math.h"
#include<math.h>

struct vector scale_vector (struct vector v, double scalar)
{
   struct vector new_v;
   new_v.x = v.x * scalar;
   new_v.y = v.y * scalar;
   new_v.z = v.z * scalar;
   return new_v;
}

double dot_vector (struct vector v1, struct vector v2)
{
   double dot_product;
   dot_product = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
   return dot_product;
}

double length_vector (struct vector v)
{
   double length;
   length = sqrt((v.x)*(v.x) + (v.y)*(v.y) + (v.z)*(v.z));
   return length;
}

struct vector normalize_vector (struct vector v)
{
   struct vector normal_v;
   double scale = 1/length_vector(v);
   normal_v = scale_vector(v,scale);
   return normal_v;
}

struct vector difference_point (struct point p1, struct point p2)
{
   struct vector difference_vector;
   difference_vector = create_vector(p1.x-p2.x,p1.y-p2.y,p1.z-p2.z);
   return difference_vector;
}

struct vector difference_vector (struct vector v1, struct vector v2)
{
   struct vector difference_vector;
   difference_vector = create_vector(v1.x-v2.x,v1.y-v2.y,v1.z-v2.z);
   return difference_vector;
}

struct point translate_point (struct point p, struct vector v)
{
   struct point new_point;
   new_point = create_point(p.x+v.x,p.y+v.y,p.z+v.z);
   return new_point;
}
   
