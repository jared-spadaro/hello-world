#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
void print_all(int argc,char*argv[])
{
   int i;
   for(i=0;i<argc;i++)
   {
   printf("%s\n",argv[i]);
   }   
}
*/
void print_all_less_than (int argc,char*argv[])
{
   int i,j;
   for(i=0;i<argc;i++)
   {
      int check1 = strcmp(argv[i],argv[0]);
      if(check1==-1)
      {
         printf("%s\n",argv[i]);
      }
   }
   printf("%s\n",argv[0]);
   for(j=0;j<argc;j++)
   {
      int check2 = strcmp(argv[j],argv[0]);
      if(check2==1)
      {
         printf("%s\n",argv[j]);
      }
   }
}


int main(int argc,char*argv[])
{
   /*
   print_all(argc,argv);
   */
   print_all_less_than(argc,argv);
   
   return 0;
}
