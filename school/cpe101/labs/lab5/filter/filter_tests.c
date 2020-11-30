#include "point.h"
#include "filter.h"
#include "checkit.h"
#include <stdio.h>

void are_positive_test_cases()
{
   double input[5] = {5,-12,-40,21,0.0001};
   double input_1[5] = {-27,-30,1,-2,-50};
   
   int size = 5;
   int size_1 = 5;
   
   double result[3];
   double result_1[1];

   int next_index = are_positive(input,size,result);
   int next_index_1 = are_positive(input_1,size_1,result_1);

   checkit_double(result[0],5);
   checkit_double(result[1],21);
   checkit_double(result[2],0.0001);
   checkit_double(next_index,3);

   checkit_double(result_1[0],1);
   checkit_double(next_index_1,1);
}

void are_greater_than_test_cases ()
{
   double n = 50;
   double n_1 = -100;
   
   double input[5] = {49.999,50,50.0001,-20,62};
   double input_1[5] = {-101,-99,200,5,0};
   
   double result[2];
   double result_1[4];
   
   int size = 5;
   int size_1 = 5;
 
   int next_index = are_greater_than(n,input,size,result);
   int next_index_1 = are_greater_than(n_1,input_1,size_1,result_1);

   checkit_double(result[0],50.0001);
   checkit_double(result[1],62);
   checkit_double(next_index,2);

   checkit_double(result_1[0],-99);
   checkit_double(result_1[1],200);
   checkit_double(result_1[2],5);
   checkit_double(result_1[3],0);
   checkit_double(next_index_1,4);
}

void are_in_first_quadrant_test_cases ()
{
   struct point input[5];
   struct point input_1[3];
   
   int size = 5;
   int size_1 = 3;
   
   struct point result[3];
   struct point result_1[1];
   
   input[0] = create_point(-3,7);
   input[1] = create_point(4,5);
   input[2] = create_point(7,12);
   input[3] = create_point(5,-1);
   input[4] = create_point(27,42);

   input_1[0] = create_point(14,20);
   input_1[1] = create_point(-2,-1);
   input_1[2] = create_point(-1,20);

   int next_index = are_in_first_quadrant(input,size,result);
   int next_index_1 = are_in_first_quadrant(input_1,size_1,result_1);
  
   checkit_double(result[0].x,4);
   checkit_double(result[0].y,5);
   checkit_double(result[1].x,7);
   checkit_double(result[1].y,12);
   checkit_double(result[2].x,27);
   checkit_double(result[2].y,42);
   checkit_double(next_index,3);

   checkit_double(result_1[0].x,14);
   checkit_double(result_1[0].y,20);
   checkit_double(next_index_1,1);

   
}

int main (void)
{
   are_positive_test_cases();
   are_greater_than_test_cases();
   are_in_first_quadrant_test_cases();  
   return 0;
}
