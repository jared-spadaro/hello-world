#include <stdio.h>

void vaTotal (int num, ...) {
   int *pi, subTot = 0;
   pi = &num;
   while(num--) {
      subTot += *++pi;
      printf("Running subtotal: %d\n",subTot);
   }
  // pi++;
   **(int **)++pi += subTot;
}


int main () {
   int i, sum = 42;
   short s;
   char c;

   scanf("%d %hd %c", &i, &s, &c);
   vaTotal(3, i, s, c, &sum);
   printf("\n\n\n");
   vaTotal(4, c, c, s, i, &sum);

   printf("Sum = %d\n", sum);

   return 0;
}
