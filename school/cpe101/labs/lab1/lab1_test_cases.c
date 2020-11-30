/*
 * Test cases example for lab 1.
 */

#include <stdio.h>
#include "checkit.h"

void test_cases(void)
{
   checkit_int(0 + 1, 1);
   checkit_int(2 * 2, 4);
   checkit_int(19 / 3, 6);
   checkit_double(19.0 / 3, 6.333333);
   checkit_double(19 / 3.0, 6.333333);
   checkit_double(19.0 / 3.0, 6.333333);
   checkit_int(4 * 2 + 27 / 3 + 4, 21);
   checkit_int(4 * (2 + 27) / 3 + 4, 42) ;
}

int main(int argc, char **argv)
{
   test_cases();

   return 0;
}
