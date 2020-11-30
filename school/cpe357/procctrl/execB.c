#include <stdio.h>
#include <unistd.h>

#define MIN 3

int main(int argc, char **argv) {
   char **ptr;

   for (ptr = argv + 1; *ptr; ptr++)
      printf("%s ", *ptr);
   printf("\n");

   if (argc > MIN) {
      argv[1] = *argv;
      argv[argc - 1] = NULL;
      argv++;
      execv(*argv, argv);
   }
   printf("Done!\n");

   return 0;
}
