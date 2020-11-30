#include "checkit.h"
#include <strings.h>
#include "strcmp.h"

void strcmp_test_cases()
{
   char s1[] = "-eye";
   char s2[] = "-eye";
   int compare = strcmp(s1,s2);
   checkit_int(compare,0);
}

void strcmp_loop_test_cases()
{
   char * cmdline[] = {"jared", "spadaro", "is", "-awesome"};
   char flag[] = "-awesome";
   char flag1[] = "is";
   char flag2[] = "rock";
   int num_args = 4;
   int check = flag_finder(cmdline,flag,num_args);
   int check1 = flag_finder(cmdline,flag1,num_args);
   int check2 = flag_finder(cmdline,flag2,num_args);
   checkit_int(check,3);
   checkit_int(check1,2);
   checkit_int(check2,0);
}

int main (void)
{
   strcmp_test_cases();
   strcmp_loop_test_cases();
   return 0;
}