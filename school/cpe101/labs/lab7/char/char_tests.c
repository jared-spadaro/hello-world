#include "char.h"
#include "checkit.h"
#include <stdio.h>

void is_lower_101_test_cases()
{
   char d = 'd';
   char D = 'D';
   char K = 'K';
   char e = 'e';
   int lower = is_lower_101(d);
   int lower1 = is_lower_101(D);
   int lower2 = is_lower_101(K);
   int lower3 = is_lower_101(e);
   checkit_int(lower,1);
   checkit_int(lower1,0);
   checkit_int(lower2,0);
   checkit_int(lower3,1);
}
   
void char_rot_13_test_cases ()
{
   char f = 'f';
   char q = 'q';
   char C = 'C';
   char R = 'R';
   char rot13 = char_rot_13(f);
   char rot14 = char_rot_13(q);
   char rot15 = char_rot_13(C);
   char rot16 = char_rot_13(R);
   checkit_char(rot13,'s');
   checkit_char(rot14,'d');
   checkit_char(rot15,'P');
   checkit_char(rot16,'E');
}

















int main (void)
{
   is_lower_101_test_cases();
   char_rot_13_test_cases();
   return 0;
}
