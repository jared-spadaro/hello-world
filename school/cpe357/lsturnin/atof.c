#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include "Report.h"


int main () {
   char *s = ".1234";
   double d = atof(s);
   printf("Double = %.3lf\n", d);

   double neg = 0;
   printf("negative zero = %lf\n", neg*-1);

   return 0;
}
