#include "commandline.h"
#include <stdio.h>
#include <stdlib.h>




int main (int argc, char*argv[])
{
   FILE * output = fopen("image.ppm","w");
   FILE * input = open_file(argv[1]);
   read_and_print(input,output,argc,argv);
   fclose(output);
   fclose(input);
   return 0;
}