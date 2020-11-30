#include "string.h"
#include "checkit.h"
#include <stdio.h>

void str_rot_13_test_cases()
{
   char input [4] = {'a','b','c','\0'};
   char input_1 [4] = {'x','y','z','\0'};
   char input_2 [4] = {'R','F','J','\0'};
   char result [4];
   char result_1 [4];
   char result_2 [4];
   str_rot_13(input,result);
   str_rot_13(input_1,result_1);
   str_rot_13(input_2,result_2);
   checkit_char(result[0],'n');
   checkit_char(result[1],'o');
   checkit_char(result[2],'p');
   checkit_char(result[3],'\0');

   checkit_char(result_1[0],'k');
   checkit_char(result_1[1],'l');
   checkit_char(result_1[2],'m');
   checkit_char(result_1[3],'\0');

   checkit_char(result_2[0],'E');
   checkit_char(result_2[1],'S');
   checkit_char(result_2[2],'W');
   checkit_char(result_2[3],'\0');
}


void str_cat_101_test_cases()
{
   char input1[] = "jared\0";
   char input2[] = "spadaro\0";
   char result[13];
   str_cat_101(input1,input2,result);
   checkit_char(result[0],'j');
   checkit_char(result[1],'a');
   checkit_char(result[2],'r');
   checkit_char(result[3],'e');
   checkit_char(result[4],'d');
   checkit_char(result[5],'s');
   checkit_char(result[6],'p');
   checkit_char(result[7],'a');
   checkit_char(result[8],'d');
   checkit_char(result[9],'a');
   checkit_char(result[10],'r');
   checkit_char(result[11],'o');
   checkit_char(result[12],'\0');
}






int main (void)
{
   str_rot_13_test_cases();
   str_cat_101_test_cases();
   return 0;
}
