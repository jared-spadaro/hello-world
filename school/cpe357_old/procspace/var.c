#include <stdio.h>

void variadic (int x, ...) {
   int i,*q,*p = &x;
   for(i=5;i>0;i--) {
      q = ++p;
      printf("%d\n",*q);
   }
}

int main () {
   variadic(4,5,6,7,8,9);
   return 0;
}
