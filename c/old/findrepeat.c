#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LEN 100
#define NUM_LETTERS 26

char *readArg(char *str) {
   printf("Enter string to analyze: ");
   scanf("%s", str);
   return str;
}

void findRepeat(char *str) {
   char curr = 0, i = 0;
   char *countArr = calloc(NUM_LETTERS, sizeof(char));
   while (str[i] != '\0') {
      countArr[tolower(str[i++])]++;
   }
   i = 0;
   while (str[i] != '\0') {
      if (countArr[tolower(str[i])] == 1) {
         printf("First non-repeated letter is \'%c\'\n", str[i]);
         exit(0);
      }  
      i++;
   }
}

int main(void) {
   char str[MAX_LEN];
   findRepeat(readArg(str));  
   return 0;
}
