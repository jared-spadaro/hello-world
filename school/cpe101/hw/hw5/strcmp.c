#include "strcmp.h"

int strcmp(char const s1[],char const s2[])
{
   int i;
   for(i=0;s1[i]!='\0'&&s2[i]!='\0';i++)
   {
      if(s1[i]!=s2[i])
	  {
	     if(s1[i]<s2[i])
		 {
		    return -1;
	     }
		 else
		 {
		    return 1;
	     }
	  }
	}
	return 0;
}
	      
		  
		  
int flag_finder (char * cmdline[],char flag[],int num_args)
{
   int i;
   
   for(i=0;i<num_args;i++)
   {
      if(strcmp(cmdline[i],flag)==0)
	  {
	     return i;
      }
   }
   return 0;
}

















		  
		  