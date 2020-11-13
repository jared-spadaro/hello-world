#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>

#define LEFT_SQUARE '['
#define RIGHT_SQUARE ']'
#define LEFT_PAREN '('
#define RIGHT_PAREN ')'
#define LEFT_CURLY '{'
#define RIGHT_CURLY '}'

bool isValid(char *s) {
   int i;
   bool ret = true, open_square = false, open_paren = false, open_curly = false;
   if (strlen(s) == 0) return ret;
   
   for (i = 0; i < strlen(s); i++) {
      if (s[i] == LEFT_SQUARE) {
         if(!open_square) open_square = true;
         else ret = false;
      }
      else if (s[i] == LEFT_PAREN) {
         if(!open_paren) open_paren = true;
         else ret = false;
      }
      else if (s[i] == LEFT_CURLY) {
         if(!open_curly) open_curly = true;
         else ret = false;
      }
      else if (s[i] == RIGHT_SQUARE) {
         if (!open_square) ret = false;
         else open_square = false;
      }     
      else if (s[i] == RIGHT_PAREN) {
         if (!open_paren) ret = false;
         else open_paren = false;
      }
      else if (s[i] == RIGHT_CURLY) {
         if (!open_curly) ret = false;
         else open_curly = false;
      }
      else {
         ret = false;
      }

      if (!ret) i = strlen(s);
   } 
   return ret;
}

int main() {
   char *s = malloc(20);
   printf("Enter string to be parsed: ");
   scanf("%s", s);
   printf("The result is %d\n", isValid(s));
   return 0;
}

