#include "while.h"
#include "checkit.h"

void while_test_cases()
{
   int expected3[3] = {0, 1, 2};
   int result3[3];

   int expected5[5] = {0, 1, 2, 3, 4};
   int result5[5];

   int i;

   while_version(result3, 3);
   for (i = 0; i < 3; i++)
   {
      checkit_int(result3[i], expected3[i]);
   }

   while_version(result5, 5);
   for (i = 0; i < 5; i++)
   {
      checkit_int(result5[i], expected5[i]);
   }
}

void for_test_cases()
{
   int expected3[3] = {0, 1, 2};
   int result3[3];

   int expected5[5] = {0, 1, 2, 3, 4};
   int result5[5];

   int i;

   for_version(result3, 3);
   for (i = 0; i < 3; i++)
   {
      checkit_int(result3[i], expected3[i]);
   }

   for_version(result5, 5);
   for (i = 0; i < 5; i++)
   {
      checkit_int(result5[i], expected5[i]);
   }
}

void test_cases()
{
   while_test_cases();
   for_test_cases();
}

int main(void)
{
   test_cases();

   return 0;
}
