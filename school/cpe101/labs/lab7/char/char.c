#include "char.h"

int is_lower_101(char c)
{
   return (c>='a' && c<='z');   
}

char char_rot_13(char c)
{
   if((c>='a'&&c<='m')||(c>='A'&&c<='M'))
      {
      return c + 13;
      }
      else 
      {
      return c - 13;
      }
 
}
