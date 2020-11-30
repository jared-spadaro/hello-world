#include "data.h"
#include "vector_math.h"
#include <math.h>



struct maybe_point sphere_intersection_point(struct ray r, struct sphere s)
{
   double t1;
   double t2;
   double A;
   double B;
   double C;
   double discriminant;
   struct point translate_0;
   struct point translate_1;
   struct point translate_2;
   struct maybe_point not_a_point;
   struct maybe_point a_point_1;
   struct maybe_point a_point_2;
   
   r.dir = normalize_vector(r.dir);

   A = dot_vector(r.dir, r.dir);
   B = 2 * dot_vector((difference_point(r.p, s.center)), r.dir);
   C = dot_vector(difference_point(r.p,s.center),(difference_point(r.p,s.center))) - (s.radius * s.radius);

   discriminant = (B*B) - (4*A*C);
   
   t1 = (-B + sqrt((B*B) - (4*A*C))) / (2*A);
   t2 = (-B - sqrt((B*B) - (4*A*C))) / (2*A);

   translate_0 = create_point (0,0,0);
   translate_1 = translate_point(r.p,scale_vector(r.dir,t1));
   translate_2 = translate_point(r.p,scale_vector(r.dir,t2));

   not_a_point = create_maybe_point (0,translate_0);
   a_point_1 = create_maybe_point (1,translate_1);
   a_point_2 = create_maybe_point (1,translate_2);


   
   if (discriminant < 0)
   {
       return not_a_point;
   }
   else 
   {
       if (t1 > 0 && t2 > 0)
       {
          if (t1 < t2)
          {
             return a_point_1;
          }
          else
          {
             return a_point_2;
          }
       }
       else if (t1 > 0 && t2 < 0)
       {
          return a_point_1;
       }
       else if (t2 > 0 && t1 < 0)
       {
          return a_point_2;
       }
       else
       {
          return not_a_point;
       }
   }
}


int find_intersection_points(struct sphere const spheres[],int num_spheres,struct ray r,struct sphere hit_spheres[],struct point intersection_points[])
{
   int i;
   int num_spheres_hit = 0;
   struct maybe_point mp;
   for (i=0;i<num_spheres;i++)
   {
      mp = sphere_intersection_point(r,spheres[i]);
      if (mp.isPoint == 1)
      {
         intersection_points[num_spheres_hit] = mp.p;
         hit_spheres[num_spheres_hit] = spheres[i];
         num_spheres_hit++;
      }
   }
   return num_spheres_hit;
}

struct vector sphere_normal_at_point(struct sphere s,struct point p)
{
   struct vector vec = difference_point(p,s.center);
   vec = normalize_vector(vec);
   return vec;
}

   


