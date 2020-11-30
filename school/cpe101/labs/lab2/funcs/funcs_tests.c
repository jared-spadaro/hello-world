#include <stdio.h>
#include "checkit.h"
#include "funcs.h"


void square_test_cases(void)
{
checkit_double (square(5.0), 25.0);
checkit_double (square(12.0), 144.0);
}

void cube_test_cases(void)
{
checkit_double (cube(4.0), 64.0);
checkit_double (cube(5.0), 125.0);
}

void f_test_cases(void)
{
checkit_double (f(2.0), 32.0);
checkit_double (f(3.0), 69.0);
}

void g_test_cases(void)
{
checkit_double (g(6.0, 4.0), 52.0);
checkit_double (g(3.0, 5.0), 34.0);
}

void hypotenuse_test_cases(void)
{
checkit_double (hypotenuse(3.0, 4.0), 5.0);
checkit_double (hypotenuse(5.0, 7.0), 8.602325);
}

void is_positive_test_cases(void)
{
checkit_int (is_positive(-5), 0);
checkit_int (is_positive(17), 1);
}

int main(int argc, char **argv)
{
   square_test_cases();
   cube_test_cases();
   f_test_cases();
   g_test_cases();
   hypotenuse_test_cases();
   is_positive_test_cases();

   return 0;
}
