#include "count.h"
#include "checkit.h"
#include <stdio.h>

void count_value_test_cases()
{
   int input[6] = {5,8,5,4,5,43};
   int input_1[9] = {34,21,40,56,21,21,21,5,21};
   
   int length = 6;
   int length_1 = 9;
   
   int value = 5;
   int value_1 = 21;
   
   int count = count_value(input,length,value);
   int count_1 = count_value(input_1,length_1,value_1);
   
   checkit_int(count,3);
   checkit_int(count_1,5);
}





int main (void)
{
   count_value_test_cases();
   return 0;
}
