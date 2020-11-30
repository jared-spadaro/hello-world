#include "translate.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>



FILE* open_file(char const name[])
{
   FILE*file = fopen(name,"r");
   if(file == NULL)
   {
      printf("Error: file not found.\n");
      exit(1);
   }
   return file;
}



void read_and_print(FILE * input,FILE * output,char orig,char mew,int cmd_arg)
{
   int result;
   char search;
   
   if(cmd_arg<=1)
   {
      printf("Error: file not found.\n");
      exit(1);
   }
   while(result!=EOF)
   {
      result = fscanf(input,"%c",&search);
      if(search == orig)
      {
         search = mew;
      }
      fprintf(output,"%c",search);
   }
}





int main (int argc, char * argv[])
{
   
   FILE * translation = fopen("translation","w");
   FILE * input = open_file(argv[3]);
   
   read_and_print(input,translation,argv[1][0],argv[2][0],argc);
   
   return 0;
}




