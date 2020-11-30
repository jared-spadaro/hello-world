#include <stdio.h>
#include "checkit.h"
#include "conditional.h"

void min_test_cases(void)
{
   double minimum = min(67.0,68.0);
   double minimum2 = min(11438.001, 11438.0001);
   double minimum3 = min(532.0, -153.0);
   double minimum4 = min(-758.0, -757.0);
   
   checkit_double(minimum,67.0);
   checkit_double(minimum2,11438.0001);
   checkit_double(minimum3,-153.0);
   checkit_double(minimum4,-758.0);
}

void max_test_cases(void)
{
   double maximum = max(53.0,54.0);
   double maximum2 = max(14085.001,14085.0001);
   double maximum3 = max(429.0, -5.0);
   double maximum4 = max(-408.0, -407.0);
  
   checkit_double(maximum,54.0);
   checkit_double(maximum2,14085.001);
   checkit_double(maximum3,429.0);
   checkit_double(maximum4,-407.0);
}

void max_of_three_test_cases(void)
{
   double maximum = max_of_three(27.0, 28.0, 29.0);
   double maximum2 = max_of_three(-12.0, 1.0, 14.0);
   double maximum3 = max_of_three(-423.0, -417.0, -417.001);
   double maximum4 = max_of_three(5978.0, 6023.0, 6023.5);

   checkit_double(maximum,29.0);
   checkit_double(maximum2,14.0);
   checkit_double(maximum3,-417.0);
   checkit_double(maximum4,6023.5);
}

void rental_late_fee_test_cases(void)
{
   int late_fee = rental_late_fee(0);
   int late_fee2 = rental_late_fee(9);
   int late_fee3 = rental_late_fee(15);
   int late_fee4 = rental_late_fee(24);
   int late_fee5 = rental_late_fee(517);

   checkit_int(late_fee,0);
   checkit_int(late_fee2,5);
   checkit_int(late_fee3,7);
   checkit_int(late_fee4,19);
   checkit_int(late_fee5,100);
}

int main(int argc, char **argv)
{
   min_test_cases();
   max_test_cases();
   max_of_three_test_cases();
   rental_late_fee_test_cases();
   return 0;
}
