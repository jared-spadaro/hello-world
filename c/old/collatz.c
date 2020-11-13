#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <limits.h>

#define MAX 1000000

void longestChain() {
   long long temp, longest = 0, len = 0, n = 1000, chain;
   while (n < MAX) {
      temp = n;
      while (temp != 1) {
         len++;
         if (temp % 2 == 0) {
            temp = temp / 2;
         }
         else {
            temp = (3 * temp) + 1;
         }
      }
      if (len > longest) {
         chain = n;
         longest = len;
      }
      n++;
      len = 0;
   }
   printf("Number with longest chain = %lld (chain length = %lld)\n", chain, longest);
}
   
    

int main(int argc, char *argv[]) {
   longestChain();
   return 0;
}


