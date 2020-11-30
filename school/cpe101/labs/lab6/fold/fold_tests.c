#include "point.h"
#include "fold.h"
#include "checkit.h"
#include <stdio.h>

void sum_test_cases()
{
   double input[5] = {45,12,7,21,30};
   double input_1[7] = {-20,34,5,-17,8,-10,0.4};
   int size = 5;
   int size_1 = 7;
   double sum_of = sum(input,size);
   double sum_of_1 = sum(input_1,size_1);

   checkit_double(sum_of,115);
   checkit_double(sum_of_1,0.4);
}

void index_of_smallest_test_cases()
{
   double input[5] = {45,0,-12,22,1};
   double input_1[2] = {243,745};
   double input_2[3] = {23,53,87};
   double size = 5;
   double size_1 = 0;
   double size_2 = 3;
   int mindex = index_of_smallest(input,size);
   int mindex_1 = index_of_smallest(input_1,size_1);
   int mindex_2 = index_of_smallest(input_2,size_2);
 
   checkit_int(mindex,2);
   checkit_int(mindex_1,-1);
   checkit_int(mindex_2,0);
}

void nearest_origin_test_cases ()
{
   struct point input[3];
   struct point input_1[4];
   
   int size = 3;
   int size_1 = 0;
   int size_2 = 4;
   
   input[0] = create_point(12,10);
   input[1] = create_point(-8,7);
   input[2] = create_point(5,-4);

   input_1[0] = create_point(3,6);
   input_1[1] = create_point(23,8);
   input_1[2] = create_point(-40,-34);
   input_1[3] = create_point(12,5);

   int nearest_index = nearest_origin(input,size);
   int nearest_index_1 = nearest_origin(input,size_1);
   int nearest_index_2 = nearest_origin(input_1,size_2);

   checkit_int(nearest_index,2);
   checkit_int(nearest_index_1,-1);
   checkit_int(nearest_index_2,0);
   
}









int main (void)
{
   sum_test_cases();
   index_of_smallest_test_cases();
   nearest_origin_test_cases();
   return 0;
}
