#include <stdio.h>
#include <unistd.h>

#define MIN 3

int main(int argc, char **argv) {
   char **ptr;

   for (ptr = argv + 1; *ptr; ptr++)
   printf("%s ", *ptr);
   printf("\n");

   if (argc > MIN) {
      for (ptr = argv + 1; *ptr; ptr++) { 
         *ptr = *(ptr + 1);               
      }                                   
      while (argc--) {                    
         printf("%s\n", *argv++);         
      }                                   
   }
   printf("Done!");

   return 0;
}