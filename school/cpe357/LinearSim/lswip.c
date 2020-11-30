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

#define MAX_CMD_LENGTH 30
#define MAX_NUM_ARGS 8
#define MAX_CELLS 50
#define MAX_OUT_FDS 3
#define MAX_IN_FDS 2


typedef struct {
   int numCells;
   int numSteps;
   double left;
   double right;
   int status;
} LinearSim;

void initLS (LinearSim *ls) {
   ls->numCells = 0;
   ls->numSteps = 0;
   ls->left = 0;
   ls->right = 0;
   ls->status = 0;
}

//0 = no match, -1 = bad num, 1 = good arg
int checkArg(char **args, int ndx, char arg, int *isNeg) {
   int rtn = 0, num = 1;
   if (args[ndx][0] == arg) {
      rtn = -1;
      if (args[ndx][num] == '-') {
         *isNeg = 1;
         num++;
      }
      if (args[ndx][num] && isdigit(*(args[ndx]+num))) {
         rtn = 1;
      }
   }
   else {
      rtn = 0;
   }
   return rtn;
}

void ReadArgs (LinearSim *ls, int numArgs, char **args) {
   int i, check, c = 0, s = 0, l = 0, r = 0, *isNeg = calloc(sizeof(int), 1);
   for (i = 1; i < numArgs; i++) { 
      if ((check = checkArg(args, i, 'C', isNeg)) != 0 && !c) {
         if (check == 1) {
            ls->numCells = strtol(args[i]+1, NULL, 10);
            c = 1;
         } 
         else { //-1 
            c = -1;
         }
      }
      else if ((check = checkArg(args, i, 'S', isNeg)) != 0 && !s) {
         if (check == 1) {
            ls->numSteps = strtol(args[i]+1, NULL, 10);
            s = 1;
         }
         else {
            s = -1;
         }
      }
      else if ((check = checkArg(args, i, 'L', isNeg)) != 0 && !l) {
         if (check == 1) {
            ls->left = atof(args[i]+1);
            if (*isNeg) {
               ls->left *= -1;
            }
            l = 1;
         }
      }
      else if ((check = checkArg(args, i, 'R', isNeg)) != 0 && !r) {
         if (check == 1) {
            ls->right = atof(args[i]+1);
            if (*isNeg) {
              ls->left *= -1;
            }
            r = 1;
         }
      }
      else { }
   }
   if((ls->numCells < 2 && r)|| !c || !s) {
      fprintf(stderr, "Usage: LinearSim C S L R (in any order)\n");
      exit(EXIT_FAILURE);
   }   
}

void printLS (LinearSim *ls) {
   printf("NumCells = %d\n", ls->numCells);
   printf("NumSteps = %d\n", ls->numSteps);
   printf("Left value = %.3lf\n", ls->left);
   printf("Right value = %.3lf\n", ls->right);
}

void parseCmd (char *oldCmd, char **newCmd) {
   int i;
   newCmd[0] = "./Cell";
   newCmd[1] = strtok(oldCmd, " ");
   for (i = 2; i <= MAX_NUM_ARGS; i++) {
      newCmd[i] = strtok(NULL, " ");
   }
   for (i = 0; i <= MAX_NUM_ARGS; i++) {
      //printf("%s ", newCmd[i]);
   }
   //printf("\n");
}

void genCellCmd(char *cmd, char **goodCmd, int numSteps, int *outFDs, int *inFDs, double value, int ID) {
   int i = 0;
   char *temp = calloc(sizeof(char), 5);
   sprintf(cmd, "S%d ", numSteps);
   while (outFDs[i] && i < MAX_OUT_FDS) {
      sprintf(temp, "O%d ", outFDs[i++]);
      strcat(cmd, temp);
   }
   i = 0;
   while (inFDs[i] && i < MAX_IN_FDS) {
      sprintf(temp, "I%d ", inFDs[i++]);
      strcat(cmd, temp);  
   }
   if (value) {
      sprintf(temp, "V%lf ", value);
      strcat(cmd, temp);
   }
   sprintf(temp, "D%d ", ID);
   strcat(cmd, temp);
   parseCmd(cmd, goodCmd);
}

void waitForAndPrintCells(LinearSim *ls, int *childPIDs, int inFD) {
   int pid, step, currCell, tooFewReports = 0, tooManyReports = 0;
   int bytesRead = 1, status, numCells = ls->numCells, numSteps = ls->numSteps;
   int *reportCounts = calloc(sizeof(int), numCells);
   Report *r = calloc(sizeof(Report), 1);
   printf("before wait loop...\n");
   for (currCell = 0; currCell < numCells; currCell++) {
      //printf("Child PID = %d\n", childPIDs[currCell]);
      //wait(&status);
      printf("(%d) before wait call...\n", currCell);
      pid = waitpid(childPIDs[currCell], &status, 0);
      printf("(%d) after wait call...\n", currCell);
      if(WIFEXITED(status)) {
         //printf("Status = %d, Return value (pid) = %d\n", WEXITSTATUS(status), pid);
         if (WEXITSTATUS(status)) {
            fprintf(stderr, "Error: Child %d exited with %d\n", currCell, WEXITSTATUS(status));
            ls->status = 1;
         }
      }
      else {
         fprintf(stderr, "Error: child abnormally terminated\n");
         exit(EXIT_FAILURE);
      }
   }
   printf("after wait loop...\n"); 
   while (bytesRead > 0) {
      bytesRead = read(inFD, r, sizeof(Report));
      if (bytesRead == sizeof(Report)) {
         reportCounts[r->id]++;
         printf("Result from %d, step %d: %.3lf\n", r->id, r->step, r->value);
      }
   }
   for (currCell = 0; currCell < numCells; currCell++) {
      //printf("Cell %d reported %d reports\n", currCell, reportCounts[currCell]);
      if (reportCounts[currCell] < numSteps + 1) {
         tooFewReports++;
      }
      if (reportCounts[currCell] > numSteps + 1) {
         tooManyReports++;
      }
   }
  
   if (tooFewReports) {
      fprintf(stderr, "Error: %d cells reported too few reports\n", tooFewReports);
      ls->status = 1;
   }
   if (tooManyReports) {
      fprintf(stderr, "Error: %d cells reported too many reports\n", tooManyReports);
      ls->status = 1;
   }
   close(inFD);
}

void pipeCells(LinearSim *ls) {
   int childPIDs[MAX_CELLS];
   int outFDs[MAX_OUT_FDS] = {0}, inFDs[MAX_IN_FDS] = {0};
   int numCells, currCell, childPID;
   double value = 0;
   int mainFDs[2] = {0, 0}, toNextFDs[2] = {0, 0}, fromNextFDs[2] = {0, 0};             
   int inFD = -1, outFD = -1, oldIn = -1, oldOut = -1, numIn = 0, numOut = 0;      
   char *cmd = calloc(sizeof(char), MAX_CMD_LENGTH);
   char **goodCmd = calloc(sizeof(char *), MAX_NUM_ARGS);
   pipe(mainFDs);                    
   numCells = ls->numCells;
   for (currCell = 0; currCell < numCells; currCell++) {
      if (currCell > 0 && currCell < numCells - 1) {
         pipe(fromNextFDs);
      }
      if (currCell < numCells - 2) {
         pipe(toNextFDs);
      }
      if ((childPID = fork()) < 0) {   
         perror("fork");
         exit(EXIT_FAILURE);
      }
      else if (childPID) {           //parent
         childPIDs[currCell] = childPID;
         /*if (oldOut > 0) {
            close(oldOut); 
         }
         if (oldIn > 0) {
            close(oldIn); 
         }*/
         if (inFD > 0) {
            close(inFD);  
         }
         if (outFD > 0) {
            close(outFD); 
         }
         if (currCell < numCells - 1) {
            inFD = toNextFDs[0];     
            outFD = fromNextFDs[1];  
            oldIn = fromNextFDs[0];  
            oldOut = toNextFDs[1];   
         }
         else { 
            close(fromNextFDs[0]);
            close(fromNextFDs[1]); 
            close(mainFDs[1]);
         }
      }
      else {                        //child
         close(mainFDs[0]);
         outFDs[0] = mainFDs[1];

         if (oldIn > 0) {           //NEW NEW NEW NEW NEW NEW
            close(oldIn);
         }
         if (oldOut > 0) {
            close(oldOut);
         }

         if (currCell == 0) {
            close(toNextFDs[0]);         //NEW
            value = ls->left;
            outFDs[1] = toNextFDs[1];
         }
         else if (currCell > 0 && currCell < numCells - 1) {  
            if (currCell < numCells - 2) close(toNextFDs[0]);         //NEW
            close(fromNextFDs[1]);       //NEW

            inFDs[0] = inFD;            
            inFDs[1] = fromNextFDs[0];  
            if (currCell == numCells - 2) {
               outFDs[1] = outFD;
            }
            else {            
               outFDs[1] = toNextFDs[1];  
               if (currCell > 1) {
                  outFDs[2] = outFD;       
               }
            }
         }
         else {  //rightmost cell
            value = ls->right;
            outFDs[1] = fromNextFDs[1];
         }     
         genCellCmd(cmd, goodCmd, ls->numSteps, outFDs, inFDs, value, currCell);
         execv(goodCmd[0], goodCmd);
         perror("exec:");
         exit(0);
      }
   }
   waitForAndPrintCells(ls, childPIDs, mainFDs[0]);
}

      

int main (int argc, char **argv) {
   printf("will any output print to screen?...\n");
   LinearSim *ls = calloc(sizeof(LinearSim), 1);
   initLS(ls);
   ReadArgs(ls, argc, argv);
   //printLS(ls);
   pipeCells(ls);

   /*char *cmd = calloc(sizeof(char), MAX_CMD_LENGTH);
   int outFDs[3] = {4, 8, 6};
   int inFDs[2] = {10, 3};
   genCellCmd(cmd, 4, outFDs, inFDs, 0, 7);
   printf("Cell Command = %s\n", cmd);

   char **newCmd = calloc(sizeof(char *), MAX_NUM_ARGS);
   parseCmd(cmd, newCmd);*/

   

   return ls->status;
}







