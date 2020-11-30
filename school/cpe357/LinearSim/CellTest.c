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

#define NUMFORKS 2
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
      if (i == 0) {
         pipe(pipeFDs);
      }
      if ((childPID = fork()) < 0) {
         printf("Error: bad fork call\n");
      }
      else if (childPID) {  //parent branch
         printf("Entered parent branch\n");
         if (inFD >= 0) {
            close(inFD);
         }
         if (i == 0) {
            inFD = pipeFDs[0]; //next child will read this
         }  
         //close(pipeFDs[0]); //parent will not read from pipe
         //write(pipeFDs[1], data, sizeof(Report));
         if (i == 0) {
            close(pipeFDs[1]);
         }
      }
      else {  //child branch
         printf("Entered child branch\n");
         sprintf(d, "D%d", i);
         if (i == 0) { //this child will write 
            close(pipeFDs[0]); //doesn't read pipe; it writes it
            sprintf(o, "O%d", pipeFDs[1]);
            cellCMD[2] = o;
            cellCMD[3] = v;
            cellCMD[4] = d; 
            printf("just before exec\n");
            printf("%s %s %s %s %s\n", cellCMD[0], cellCMD[1], cellCMD[2], cellCMD[3], cellCMD[4]);
            execv(cellCMD[0], cellCMD);
            perror("Exec");
         }
         else { //this child will read what the other child wrote
            //close(pipeFDs[1]); //doesn't write to pipe, it reads it
            sprintf(in, "I%d", inFD);
            cellCMD[2] = in;
            cellCMD[3] = d;
            printf("just before exec\n");
            printf("%s %s %s %s\n", cellCMD[0], cellCMD[1], cellCMD[2], cellCMD[3]);
            execv(cellCMD[0], cellCMD);
            perror("Exec"); 
         }
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
   
