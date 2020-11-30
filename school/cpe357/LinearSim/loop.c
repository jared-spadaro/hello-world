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

#define NUMFORKS 3
#define MAX_CMD 20

void sendData () {
   int i, status, childPID, pipeFDs[2];
   char **cellCMD = calloc(sizeof(char *), MAX_CMD); 
   cellCMD[0] = "./Cell";
   cellCMD[1] = "S5";
   char *o = calloc(sizeof(char), 2);
   char *in = calloc(sizeof(char), 2);
   char *v = "V3.4";
   char *d = calloc(sizeof(char), 2);
   int inFD = -1, outFD = -1;
   for (i = 0; i < NUMFORKS; i++) {
      pipe(pipeFDs);
      printf("Pipe in (parent) = %d\n", pipeFDs[0]);
      printf("Pipe out (parent) = %d\n", pipeFDs[1]);
      
      if ((childPID = fork()) < 0) {
         printf("Error: bad fork call\n");
      }
      else if (childPID) {  //parent branch
         //close(pipeFDs[0]);
         //close(pipeFDs[1]);
         /*printf("Entered parent branch\n");
         if (inFD >= 0) {
            close(inFD);
         }
         if (i < NUMFORKS-1) {
            inFD = pipeFDs[0]; //next child will read this
         }  
         close(pipeFDs[1]);*/
      }
      else {  //child branch
         printf("Pipe in (child) = %d\n", pipeFDs[0]);
         printf("Pipe out (child) = %d\n", pipeFDs[1]);
         sleep(2);
         //close(pipeFDs[0]);
         //close(pipeFDs[1]);
         //sprintf(o, "O%d", pipeFDs[1]);
         //if (i == 0) { //leftmost cell --> fixed value
         exit(0);
            
      }
   }
   for (i = 0; i < NUMFORKS; i++) { 
      wait(&status);
   }
   if(status == EXIT_FAILURE) printf("EXIT_FAILURE\n");
   if (status == EXIT_SUCCESS) printf("EXIT_SUCCESS\n");
}

int main () {
   sendData();
   return 0;
}
   
