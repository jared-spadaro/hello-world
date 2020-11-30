#include "poly.h"
#include <stdio.h>
#include "checkit.h"

void poly_add2_test_cases ()
{
   double poly1[3] = {2.5, 5.8, 4.5};
   double poly2[3] = {6.8, 1.7, 8.9};
   double poly3[3] = {12.6, 35.6, 85.7};
   double poly4[3] = {76.4, 25.4, 26.4};
   
   double result1[3];
   double result2[3]; 

   poly_add2 (poly1, poly2, result1);
   poly_add2 (poly3, poly4, result2);

   checkit_double (result1[0],9.3);
   checkit_double (result1[1],7.5);
   checkit_double (result1[2],13.4);
   
   checkit_double (result2[0],89.0);
   checkit_double (result2[1],61.0);
   checkit_double (result2[2],112.1);
}

void poly_mult2_test_cases()
{
   double poly1[3] = {3.0,5.0,4.0};
   double poly2[3] = {2.0,1.0,9.0};
   double poly3[3] = {72.0,45.0,17.0};
   double poly4[3] = {33.0,24.0,81.0};

   double result1[5];
   double result2[5];

   poly_mult2(poly1,poly2,result1);
   poly_mult2(poly3,poly4,result2);

   checkit_double(result1[0],6.0);
   checkit_double(result1[1],13.0);
   checkit_double(result1[2],40.0);
   checkit_double(result1[3],49.0);
   checkit_double(result1[4],36.0);

   checkit_double(result2[0],2376.0);
   checkit_double(result2[1],3213.0);
   checkit_double(result2[2],7473.0);
   checkit_double(result2[3],4053.0);
   checkit_double(result2[4],1377.0);
}












int main (void)
{
   

   poly_add2_test_cases();
   poly_mult2_test_cases();


   return 0;
}
