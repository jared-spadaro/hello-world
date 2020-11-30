#include <stdlib.h>
#include <stdio.h>

#define BUF_LEN 30
#define STACK_SIZE 4096

void Uncalled() {
   printf("Uncalled was called. Strange that.\n");
   exit(-1);
}

void Prompt() {
   char buf[BUF_LEN];
   printf("Enter your name:\n");
   scanf("%s", buf);
   printf("Your name is: %s\n", buf);
}

int main(void) {
   Prompt();
   return 0;
}
