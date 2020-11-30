#include "poly.h"
#include <stdio.h>
#include "checkit.h"

void poly_add2_test_cases ()
{
   double poly1[3] = {2.5, 5.8, 4.5};
   double poly2[4] = {6.8, 1.7, 8.9,3.0};

   int degree1 = 2;
   int degree2 = 3;

   double poly3[2] = {12.6, 35.6};
   double poly4[3] = {76.4, 25.4, 26.4};
   
   int degree3 = 1;
   int degree4 = 2;

   double result1[4];
   double result2[3]; 

   poly_add2 (poly1,degree1,poly2,degree2,result1);
   poly_add2 (poly3,degree3,poly4,degree4,result2);

   checkit_double (result1[0],9.3);
   checkit_double (result1[1],7.5);
   checkit_double (result1[2],13.4);
   checkit_double (result1[3],3.0);
   
   checkit_double (result2[0],89.0);
   checkit_double (result2[1],61.0);
   checkit_double (result2[2],26.4);
}

void poly_mult2_test_cases()
{
   double poly1[3] = {1,4,5};
   double poly2[5] = {3,2,5,1,4};
   double poly3[2] = {4.0,5.0};
   double poly4[3] = {3.0,2.0,8.0};
   

   int degree1 = 2;
   int degree2 = 4;
   int degree3 = 1;
   int degree4 = 2;

   double result1[7];
   double result2[4];

   poly_mult2(poly1,degree1,poly2,degree2,result1);
   poly_mult2(poly3,degree3,poly4,degree4,result2);

   checkit_double(result1[0],3);
   checkit_double(result1[1],14);
   checkit_double(result1[2],28);
   checkit_double(result1[3],31);
   checkit_double(result1[4],33);
   checkit_double(result1[5],21);
   checkit_double(result1[6],20);
   

   checkit_double(result2[0],12.0);
   checkit_double(result2[1],23.0);
   checkit_double(result2[2],42.0);
   checkit_double(result2[3],40.0);
   
}












int main (void)
{
   

   poly_add2_test_cases();
   poly_mult2_test_cases();


   return 0;
}
