#include <stdio.h>
#include <ctype.h>

#define NUM_LETTERS 26

int main () {
   int ch, temp, bits;
   ch = getchar();
   bits = 0;
   while(ch != EOF) {
      if(isalpha(ch)) {
         ch = toupper(ch);
         temp = 1 << ch - ((NUM_LETTERS+2) * 2 + (2*2*2) + 1);
         if((bits & temp) == 0) { //if the bit in question is a 0
            bits |= temp;
         }
         else {
            bits &= ~temp;
         }  
      }
      ch = getchar();
   }
   printf("%08X\n", bits);
   temp = 0;
   while(temp < NUM_LETTERS) {
      ch = 1 << temp;
      if((bits & ch) == 0) {
         printf("%c appears an even number of times\n", ((NUM_LETTERS+2)*2 + (2*2*2) + 1 + temp));
      }
      else {
         printf("%c appears an odd number of times \n", ((NUM_LETTERS+2)*2 + (2*2*2) + 1 + temp));
      }
      temp++;
   }




   return 0;
}
