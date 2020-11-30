#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "lwp.h"

#define INITIAL_STACK 1024

void printnum (int num) {
   printf("%d", num);
}

int main(void){
  long x = 4;
  lwp_create((lwpfun)printnum, (void*)x, INITIAL_STACK);
  lwp_create((lwpfun)printnum, (void*)x+1, INITIAL_STACK);
  lwp_create((lwpfun)printnum, (void*)x+2, INITIAL_STACK);
   
  lwp_start();
  lwp_start();
}

