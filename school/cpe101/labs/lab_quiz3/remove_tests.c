#include "remove.h"
#include "checkit.h"
#include <stdio.h>

void remove_index_test_cases()
{
   int input[5] = {4,6,8,2,3};
   int input_1[6] = {5,2,8,5,7,11};

   int length = 6;
   int length_1 = 5;

   int index = 2;
   int index_1 = 1;
   
   remove_index(input,length,index);
   remove_index(input_1,length_1,index_1);

   checkit_int(input[0],4);
   checkit_int(input[1],6);
   checkit_int(input[2],2);
   checkit_int(input[3],3);

   checkit_int(input_1[0],5);
   checkit_int(input_1[1],8);
   checkit_int(input_1[2],5);
   checkit_int(input_1[3],7);
   checkit_int(input_1[4],11);
}




int main (void)
{
   remove_index_test_cases();
   return 0;
}
