#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SmartAlloc.h"

char *ReadLine () {
   int curr, count = 0;
   char letter, *line;
   while(curr != EOF) {
      curr = getchar();
      if(curr != EOF) {
         count++;
         letter = curr;
         printf("%c",letter);
         line = malloc(sizeof(char));
         *line = letter;
      }
   }
   if(!count) {
      return NULL;
   }
   return line;
}

int main() {
char *line;

while (NULL != (line = ReadLine())) {
printf("%s (%d)\n", line, report_space());
free(line);
}

return 0;
}
