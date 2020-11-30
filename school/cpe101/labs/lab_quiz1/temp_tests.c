#include "temp.h"
#include "checkit.h"
#include <stdio.h>

void cent_to_fahr_test_cases (void)
{
   double fahr1;
   double fahr2;
   fahr1 = cent_to_fahr (45.0);
   fahr2 = cent_to_fahr (-27.0);
   checkit_double(fahr1,113.0);
   checkit_double(fahr2,-16.6);
}


int main (void)
{
   cent_to_fahr_test_cases();
   return 0;
}
