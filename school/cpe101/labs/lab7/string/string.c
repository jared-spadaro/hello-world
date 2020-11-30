#include "string.h"

void str_rot_13(char const input[],char result[])
{
   int i;
   char temp;
   for(i=0;input[i]!='\0';i++)
   {
      
      
if((input[i]>='a'&&input[i]<='m')||(input[i]>='A'&&input[i]<='M'))
      {
         temp = input[i] + 13;
      }
      else
      {
         temp = input[i] - 13;
      }
      result[i] = temp;
   }
   result[i] = '\0';
}

void str_cat_101(char const input1[],char const input2[],char result[])
{
   int i,j;
   for(i=0;input1[i]!='\0';i++)
   {
      result[i] = input1[i];
   }
   for (j=0;input2[j]!='\0';j++)
   {
      result[i+j] = input2[j];
   }
   
   result[i+j] = '\0';
}
