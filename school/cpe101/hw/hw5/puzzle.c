#include <stdio.h>
#include <stdlib.h>

FILE * open_file (char const name[],char const mode[])
{
   FILE * file = fopen(name,mode);
   if(file == NULL)
   {
      printf("Usage: <input file name>\n");
      exit(1);
   }
   return file;
}

void decode_pixels (width, height)
{
   fprintf(output,"P3\n");
   fprintf(output,"%d %d\n",width,height);
   fprintf(output,"255\n");



void read_and_print (FILE * input)
{
   

















int main (void)
{
   return 0;
}
