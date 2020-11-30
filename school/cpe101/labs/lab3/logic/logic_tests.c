#include <stdio.h>
#include "checkit.h"
#include "logic.h"

void is_even_test_cases(void)
{
   int even = is_even(72);
   int even1 = is_even(4028);
   int odd = is_even(101);
   int odd1 = is_even(5047);
   checkit_int(even,1);
   checkit_int(even1,1);
   checkit_int(odd,0);
   checkit_int(odd1,0);
}

void is_between_test_cases(void)
{
   int in = is_between(5,2,12);
   int in1 = is_between(4928, 3298, 5798);
   int out = is_between(74,58,62);
   int out1 = is_between(-57,59,32);
   checkit_int(in,1);
   checkit_int(in1,1);
   checkit_int(out,0);
   checkit_int(out1,0);
}

void in_an_interval_test_cases(void)
{
   int in = in_an_interval(2);
   int in1 = in_an_interval(5);
   int out = in_an_interval(9);
   int out1 = in_an_interval(11);

   int in2 = in_an_interval(50);
   int out2 = in_an_interval(47);
   int out3 = in_an_interval(92);

   int in3 = in_an_interval(15);
   int in4 = in_an_interval(19);
   int out4 = in_an_interval(12);
   int out5 = in_an_interval(27);

   int in5 = in_an_interval(101);
   int in6 = in_an_interval(103);
   int out6 = in_an_interval(97);
   int out7 = in_an_interval(141);

   checkit_int(in,1);
   checkit_int(in1,1);
   checkit_int(out,0);
   checkit_int(out1,0);

   checkit_int(in2,1);
   checkit_int(out2,0);
   checkit_int(out3,0);

   checkit_int(in3,1);
   checkit_int(in4,1);
   checkit_int(out4,0);
   checkit_int(out5,0);

   checkit_int(in5,1);
   checkit_int(in6,1);
   checkit_int(out6,0);
   checkit_int(out7,0);


}

int main(int argc, char **argv)
{
   is_even_test_cases();
   is_between_test_cases();
   in_an_interval_test_cases();
   return 0;
}
