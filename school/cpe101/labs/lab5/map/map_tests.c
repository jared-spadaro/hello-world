#include "point.h"
#include "map.h"
#include "math.h"
#include "checkit.h"
#include <stdio.h>

void square_all_test_cases ()
{
   double input[5] = {5,8,3,6,7};
   double input_1[4] = {12,15,20,1};
   
   int size = 5;
   int size_1 = 4;
 
   double result[5];
   double result_1[4];

   square_all(input,size,result);
   square_all(input_1,size_1,result_1);
   
   checkit_double(result[0],25);
   checkit_double(result[1],64);
   checkit_double(result[2],9);
   checkit_double(result[3],36);
   checkit_double(result[4],49);

   checkit_double(result_1[0],144);
   checkit_double(result_1[1],225);
   checkit_double(result_1[2],400);
   checkit_double(result_1[3],1);
}

void add_n_all_test_cases()
{
   double n = 10;
   double n_1 = 100;
   
   double input[5] = {17,23,85,45,92};
   double input_1[4] = {233,453,746,859};
   
   int size = 5;
   int size_1 = 4;
   
   double output[5];
   double output_1[4];
   
   add_n_all(n,input,size,output);
   add_n_all(n_1,input_1,size_1,output_1);

   checkit_double(output[0],27);
   checkit_double(output[1],33);
   checkit_double(output[2],95);
   checkit_double(output[3],55);
   checkit_double(output[4],102);

   checkit_double(output_1[0],333);
   checkit_double(output_1[1],553);
   checkit_double(output_1[2],846);
   checkit_double(output_1[3],959);
}

void distance_all_test_cases()
{
   struct point input[3];
   struct point input_1[2];
   
   int size = 3;
   int size_1 = 2;
   
   double result[3];
   double result_1[2];
   
   input[0] = create_point(4,7);
   input[1] = create_point(2,5);
   input[2] = create_point(6,3);

   input_1[0] = create_point(-12,10);
   input_1[1] = create_point(-5,-7);
   
   distance_all(input,size,result);
   distance_all(input_1,size_1,result_1);

   checkit_double(result[0],8.062258);
   checkit_double(result[1],5.385165);
   checkit_double(result[2],6.708204);

   checkit_double(result_1[0],15.620499);
   checkit_double(result_1[1],8.602325);
   checkit_double(result_1[2],8.062258);   
}

int main (void)
{
   square_all_test_cases();
   add_n_all_test_cases();
   distance_all_test_cases();
   return 0;
}

