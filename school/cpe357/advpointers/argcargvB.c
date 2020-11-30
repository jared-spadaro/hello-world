#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
   
   int sum = 0, temp;
   char *end;
   
   while (--argc > 0) {
      temp = strtol(argv[argc], &end, 10);
      if (!*end) { //there were no alpha characters
         sum += temp;
      }
      else {}
   } 


   printf("Sum is %d\n", sum);
   return 0;
}
