#include "convert.h"
#include <string.h>

#include <stdio.h>



double convert_double(char const input[],double default_value)
{
   double ret_value;   
   int converted;
   converted = sscanf(input,"%lf",&ret_value);
   if(converted >= 1)
   {
      return ret_value;
   }
   return default_value;
}
