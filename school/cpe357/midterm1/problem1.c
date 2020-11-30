#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SmartAlloc.h"

#define WORD_LEN 10

char *RepeatStr(char *word, int count) {
   char *str;
   str = malloc(sizeof(char) * strlen(word) * count + 1);
   if(!count) {
      *str = '\0';
   }
   else {
      strcpy(str, word);
      while(--count) {
         strcat(str,word);
      }
   }
   return str;
}

int main() {
char *repeat, word[WORD_LEN + 1];
int count;

while (EOF != scanf("%10s %d", word, &count)) {
repeat = RepeatStr(word, count);
printf("%s repeated %d times is %s\n", word, count, repeat);
printf("%d bytes used\n", report_space());
free(repeat);
}
return 0;
}
