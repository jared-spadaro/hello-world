#include "convert.h"
#include <stdio.h>
#include <string.h>
#include "checkit.h"





void convert_double_test_cases ()
{
   char input[] = "45eyeblahblah";
   char input1[] = "fpaoiejfnep";
   double def_value = 0;
   int checker = convert_double(input,def_value);
   int checker1 = convert_double(input1,def_value);
   checkit_double(checker,45);
   checkit_double(checker1,0);
}  




















int main (void)
{
   convert_double_test_cases();
   return 0;
}
