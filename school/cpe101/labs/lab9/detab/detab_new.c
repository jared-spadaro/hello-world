#include <stdio.h>
#include <stdlib.h>

#define OUTFILE_NAME "detabbed"
#define TAB_STOP_SIZE 8
#define NUM_ARGS 2
#define FILE_ARG_IDX 1

FILE * open_infile(char const name[])
{
   FILE * file = fopen(name,"r");
   
   if (file == NULL)
   {
     perror(name);
     exit(1);
   }
   
   return file;
} 

FILE * open_outfile(char const name[])
{
   FILE * file = fopen(name,"w");
   
   if (file == NULL)
   {
     perror(name);
     exit(1);
   }
   
   return file;
}

void error_check(int arguments,char const arg1[])
{
   if (arguments < 1)
   {
      fprintf(stderr, "usage: prog file\n"); 
      exit(1);
   }
   else if (arguments < NUM_ARGS)
   {
      fprintf(stderr, "usage: %s file\n", arg1);
      exit(1);
   }
}



void read_and_print(FILE *infile,FILE *outfile)
{
   int i;
   char c;
   int character_count = 0;
   int num_spaces;
   while (fscanf(infile, "%c", &c) != EOF)
   {
      if (c == '\t')
      {
         num_spaces = TAB_STOP_SIZE - (character_count % TAB_STOP_SIZE);

         for (i = 0; i < num_spaces; i++)
         {
            fprintf(outfile, " ");
         }
         character_count = character_count + num_spaces;
      }
      else if (c == '\n')
      {
         fprintf(outfile, "\n");
         character_count = 0;
      }
      else
      {
         fprintf(outfile, "%c", c);
         character_count = character_count + 1;
      }
   }
}




int main (int argc, char*argv[])
{
   error_check(argc,argv[0]);
   FILE * outfile = open_outfile("detabbed");
   FILE * infile = open_infile(argv[1]);
   
   read_and_print(infile,outfile);
   fclose(infile);
   fclose(outfile);
   return 0;
}
   






