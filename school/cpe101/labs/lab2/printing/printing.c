#include <stdio.h>



void printf_examples(void)
{
   int n = 2, m = 4;
   double f = 42.7;

   /* Place the printf calls specified in the lab description below here. */
   printf("Entered printf_examples function\n");
   printf("n: %d\n", n);
   n=99;
   printf("n: %d\tm: $d\n", n, m);
   printf("f: %f\n", f);
}


int main(int argc, char **argv)
{
   printf_examples();

   return 0;
}
