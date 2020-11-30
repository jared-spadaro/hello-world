#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Problem3.h"

#define EMPTY_STRING ""
#define MAX_SIZE 100

/* Prototype for local helper function */
void MyGetLine(char*);

int main() {
   char stringA[MAX_SIZE], stringB[MAX_SIZE], *result;
   int atIndex, space, expectedSpace;

   /* Read in test inputs */
   MyGetLine(stringA);
   MyGetLine(stringB);
   scanf("%d%d", &atIndex, &expectedSpace);

   /* If either test input string is "EMPTY_STRING", make it an empty string. */
   if (0 == strcmp("EMPTY_STRING", stringA))
      strcpy(stringA, EMPTY_STRING);

   if (0 == strcmp("EMPTY_STRING", stringB))
      strcpy(stringB, EMPTY_STRING);

   /* Call the function being tested and print the results */
   result = insert(stringA, stringB, atIndex);
   printf("|%s|\n", result);
 
   /* Print whether or not the correct amount of memory was allocated */
   space = report_space();

   if (space == expectedSpace)
      printf("Correct amount of memory allocated\n");
   else if (space > expectedSpace)
      printf("Too much memory allocated\n");
   else
      printf("Too little memory allocated\n");
   
   /* Check for memory use after free */
   free(result);
   space = report_space();

   if (space)
      printf("Unexpected memory use after free\n");

   return 0;
}

void MyGetLine(char *line) {
   int last;

   fgets(line, MAX_SIZE, stdin);
   last = strlen(line) - 1;

   if (line[last] == '\n')
      line[last] = '\0';
}
