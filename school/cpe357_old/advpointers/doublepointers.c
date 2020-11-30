#include <stdio.h>
#include <stdlib.h>

void SetupAll (int ***ppp, int *p) {
   *ppp = &p;
}

int main () {
   int i = 42, *p, **pp, ***ppp;
   SetupAll (ppp = &pp, p = &i);
   if(ppp == &pp && *ppp == &p/* && p == &i*/) {
      printf("%u %u %u %u\n", ***ppp, **pp, *p, i);
   }

   return 0;
}
