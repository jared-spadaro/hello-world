#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

#define MAX_FACTORS 100

int findNumFactors(int num) {
   int i, j = 2;
   for (i = 2; i < num/2; i++) {
      if (num % i == 0) {
         j++;
      }
   }
   return j;
}

int checkTriNums() {
   int i= 1, n = 0, f;
   while (f < 501) {
      n += i++;
      printf("Finding factors for %d...\n", n);
      f = findNumFactors(n);
   }
   return n;
}    

int main(int argc, char *argv[]) {
   printf("Answer: %d\n", checkTriNums());
   return 0;
}


