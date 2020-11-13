#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <stdint.h>

/* function prototypes */
int reverse(int);
int tensExp(int);

int reverse(int x) {
   int32_t new = 0, temp = x, i = 0, numdigits = 0, power = 1;
   int32_t digits[10];
   if (temp < 0) temp *= -1;
   while (temp > 0) {
      digits[i] = temp % (10 * power);
      if (digits[i] != 0) {
         temp -= digits[i];
         digits[i] /= tensExp(i);
      }
      power *= 10;
      numdigits++;
      i++;
   }
   printf("numdigits = %d\nlast digit = %d\n", numdigits, digits[numdigits - 1]);
   if (numdigits > 10 || (numdigits > 9 && digits[numdigits - 1] > 2)) {
      new = 0;
   }
   else {
      for (i = 0; i < numdigits; i++) {
         temp = digits[i] * tensExp(numdigits - (i + 1));
         printf("temp = %d\n", temp);
         if (new > INT32_MAX - temp) {
            printf("hit max\n");
            new = 0;
            i = numdigits;
         }
         else {
            new += temp;
         }
      }
   }
   if (new < 0) new = 0;
   if (x < 0) new *= -1;
   printf("result = %d\n", (int)new);       
   return 0;
}

int tensExp (int power) {
   int i, ret = 1;
   for (i = 0; i < power; i++) {
      ret *= 10;
   } 
   return ret;
}

int main(void) {
   int input;
   printf("Enter number: ");
   scanf("%d", &input);
   printf("You entered: %d\n", input);
   reverse(input);  
   return 0;
}
