#include <stdio.h>
#include <string.h>

int main () {
   int i;
   for(i=0; i<200; i++) {
      fprintf(stderr, "%s\n", strerror(i));
   }
   return 0;
}
