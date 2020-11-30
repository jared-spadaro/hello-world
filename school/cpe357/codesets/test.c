#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "SmartAlloc.h"
int main () {
   char *data1 = malloc(2);
   char *data2 = malloc(5);
   scanf("%c%c", data1, data2);
   printf("Space used = %d\n", report_space());
   free(data2);
   free(data1);
   printf("Space used = %d\n", report_space());
   


   /*int i = 5;
   while(i--) {
      printf("i = %d\n", i);
   }


   char *str = malloc(2);
   printf("Enter string: ");
   scanf("%s", str);
   strcat(str, "this is the end string");
   printf("Concatenated string = %s\n", str);*/
   return 0;
}
