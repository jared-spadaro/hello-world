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
#define MAX_ARG_LENGTH 20
#define BASE_TEN 10
#define CELL 'C'
#define STEP 'S'
#define LEFT 'L'
#define RIGHT 'R'

typedef struct {
   int numCells;
   int numSteps;
   double left;
   double right;
   int status;
} LinearSim;

void InitLS(LinearSim *lsm) {
   lsm->numCells = 0;
   lsm->numSteps = 0;
   lsm->left = 0;
   lsm->right = 0;
}

int CheckArg(char **args, int ndx, char arg, int *isNeg) {
   int rtn = 0, num = 1;

   if (args[ndx][0] == arg) {
      rtn = -1;
      if (args[ndx][num] == '-') {
         *isNeg = 1;
         num++;
      }
      if (args[ndx][num] && args[ndx][num] == '.') {
         num++;
      }
      if (args[ndx][num] && isdigit(*(args[ndx] + num))) {
         rtn = 1;
      }
   }
   else {
      rtn = 0;
   }
   return rtn;
}

void ReadArgs(LinearSim *lsm, int numArgs, char **args) {
   int ndx, check, cell = 0, step = 0, left = 0, right = 0; 
   int *isNeg = calloc(sizeof(int), 1);

   for (ndx = 1; ndx < numArgs; ndx++) { 
      if ((check = CheckArg(args, ndx, CELL, isNeg)) != 0 && !cell) {

         if (check == 1) {
            lsm->numCells = strtol(args[ndx] + 1, NULL, BASE_TEN);
            cell = 1;
         } 
         else {
            cell = -1;
         }
      }
      else if ((check = CheckArg(args, ndx, STEP, isNeg)) != 0 && !step) {
         if (check == 1) {
            lsm->numSteps = strtol(args[ndx] + 1, NULL, BASE_TEN);
            step = 1;
         }
         else {
            step = -1;
         }
      }
      else if ((check = CheckArg(args, ndx, LEFT, isNeg)) != 0 && !left) {
         if (check == 1) {
            lsm->left = atof(args[ndx] + 1);
            left = 1;
         }
      }
      else if ((check = CheckArg(args, ndx, RIGHT, isNeg)) != 0 && !right) {
         if (check == 1) {
            lsm->right = atof(args[ndx] + 1);
            right = 1;
         }
      }
      else { 
      }
   }
   if ((lsm->numCells < 2 && right) || !cell || !step) {
      fprintf(stderr, "Usage: LinearSim C S L R (in any order)\n");
      exit(EXIT_FAILURE);
   }
}

void ParseCmd(char *oldCmd, char **newCmd) {
   int ndx;

   newCmd[0] = "./Cell";
   newCmd[1] = strtok(oldCmd, " ");

   for (ndx = 2; ndx <= MAX_NUM_ARGS; ndx++) {
      newCmd[ndx] = strtok(NULL, " ");
   }
}

void GenCellCmd(char *cmd, char **goodCmd, int numSteps, int *outFDs, 
 int *inFDs, double value, int id, int numCells) {
   int ndx = 0;
   char *temp = calloc(sizeof(char), MAX_ARG_LENGTH);

   sprintf(cmd, "S%d ", numSteps);
   while (outFDs[ndx] && ndx < MAX_OUT_FDS) {
      sprintf(temp, "O%d ", outFDs[ndx++]);
      strcat(cmd, temp);
   }
   ndx = 0;
   while (inFDs[ndx] && ndx < MAX_IN_FDS) {
      sprintf(temp, "I%d ", inFDs[ndx++]);
      strcat(cmd, temp);  
   }
   if (!id || id == numCells - 1) {
      sprintf(temp, "V%lf ", value);
      strcat(cmd, temp);
   }

   sprintf(temp, "D%d ", id);
   strcat(cmd, temp);
   ParseCmd(cmd, goodCmd);
}

void ReadFromMainPipe(int inFD, int *reportCounts) {
   int bytesRead = 1;
   Report *rpt = calloc(1, sizeof(Report));

   while (bytesRead > 0) {
      bytesRead = read(inFD, rpt, sizeof(Report));
      if (bytesRead == sizeof(Report)) {
         reportCounts[rpt->id]++;
         printf("Result from %d, step %d: %.3lf\n", 
          rpt->id, rpt->step, rpt->value);
      }
   }
}

void WaitForAndPrintCells(LinearSim *lsm, 
 int *childPIDs, int inFD, int *lsmStatus) {
   int status, pid, currCell, numTooFewReports = 0, numTooManyReports = 0;
   int bytesRead = 1, numCells = lsm->numCells, numSteps = lsm->numSteps;
   int *reportCounts = calloc(lsm->numCells, sizeof(int));

   char *tooFewFormat = "Error: %d cells reported too few reports\n";
   char *tooManyFormat = "Error: %d cells reported too many reports\n";
   
   ReadFromMainPipe(inFD, reportCounts);  
   
   for (currCell = 0; currCell < numCells; currCell++) {
      bytesRead = 1;
      pid = waitpid(childPIDs[currCell], &status, 0);

      if (WIFEXITED(status)) {
         if (WEXITSTATUS(status)) {
            fprintf(stderr, "Error: Child %d exited with %d\n", 
             currCell, WEXITSTATUS(status)); 
            *lsmStatus = 1;
         }
      }
      else {
         exit(EXIT_FAILURE);
      }
   }

   for (currCell = 0; currCell < numCells; currCell++) {
      if (reportCounts[currCell] < numSteps + 1) {
         numTooFewReports++;
      }
      if (reportCounts[currCell] > numSteps + 1) {
         numTooManyReports++;
      }
   }
 
   if (numTooFewReports) {
      fprintf(stderr, tooFewFormat, numTooFewReports);
      *lsmStatus = 1;
   }
   if (numTooManyReports) {
      fprintf(stderr, tooManyFormat, numTooManyReports);
      *lsmStatus = 1;
   }
   close(inFD);
}

void TrimFDs(int fd1, int fd2) {
   if (fd1 > 0) {
      close(fd1);
   }
   if (fd2 > 0) {
      close(fd2);
   }
}

void AssignFDs(int *fds1, int *fds2, int *inFD, 
 int *outFD, int *inFD2, int *outFD2) {
   *inFD = fds1[0];
   *outFD = fds1[1];
   *inFD2 = fds2[0];
   *outFD2 = fds2[1];
}  

void ParentLogic(int *inFD, int *outFD, int *oldIn, int *oldOut, int curr,
 int numCells, int *toNextFDs, int *fromNextFDs, int *mainFDs) {
   TrimFDs(*oldOut, *oldIn);
   TrimFDs(*inFD, *outFD);

   if (curr < numCells - 1) {
      AssignFDs(toNextFDs, fromNextFDs, inFD, oldOut, oldIn, outFD);               
   }
   else { 
      TrimFDs(fromNextFDs[0], fromNextFDs[1]);
      close(mainFDs[1]);
   }
}

void ChildLogic(int inFD, int outFD, int oldIn, int oldOut, int currCell, 
 int numCells, int *toNext, int *fromNext, int *mainFDs, LinearSim *lsm) {
   int outFDs[MAX_OUT_FDS] = {0}, inFDs[MAX_IN_FDS] = {0};
   double value;

   char *cmd = calloc(sizeof(char), MAX_CMD_LENGTH);
   char **goodCmd = calloc(sizeof(char *), MAX_NUM_ARGS);
   
   close(mainFDs[0]);
   outFDs[0] = mainFDs[1];
   TrimFDs(oldIn, oldOut);

   if (currCell == 0) {
      close(toNext[0]);         
      value = lsm->left;
      outFDs[1] = toNext[1];
   }

   else if (currCell > 0 && currCell < numCells - 1) {  
      close(fromNext[1]);       
      inFDs[0] = inFD;            
      inFDs[1] = fromNext[0];  

      if (currCell == numCells - 2) {
         outFDs[1] = outFD;
      }
      else {   
         close(toNext[0]);         
         outFDs[1] = toNext[1];  
         if (currCell > 1) {
            outFDs[2] = outFD;       
         }
      }
   }
   else {  
      value = lsm->right;
      outFDs[1] = fromNext[1];
   }     
   GenCellCmd(cmd, goodCmd, lsm->numSteps, outFDs, 
    inFDs, value, currCell, numCells);
   execv(goodCmd[0], goodCmd);
}

void PipeCells(LinearSim *lsm, int *status) {
   int childPIDs[MAX_CELLS]; 
   int numCells, currCell, childPID;
   int mainFDs[2] = {0}, toNextFDs[2] = {0}, fromNextFDs[2] = {0};
   int inFD = -1, outFD = -1, oldIn = -1, oldOut = -1;

   pipe(mainFDs);                    
   numCells = lsm->numCells;

   for (currCell = 0; currCell < numCells; currCell++) {
      if (currCell > 0 && currCell < numCells - 1) {
         pipe(fromNextFDs);
      }
      if (currCell < numCells - 2) {
         pipe(toNextFDs);
      }
      if ((childPID = fork()) < 0) {   
         exit(EXIT_FAILURE);
      }
      else if (childPID) {           
         childPIDs[currCell] = childPID;
         ParentLogic(&inFD, &outFD, &oldIn, &oldOut, currCell, 
          numCells, toNextFDs, fromNextFDs, mainFDs);
      }
      else {                       
         ChildLogic(inFD, outFD, oldIn, oldOut, currCell, 
          numCells, toNextFDs, fromNextFDs, mainFDs, lsm); 
      }
   }
   WaitForAndPrintCells(lsm, childPIDs, mainFDs[0], status);
}      

int main(int argc, char **argv) {
   int status = 0;
   LinearSim *lsm = calloc(sizeof(LinearSim), 1);

   InitLS(lsm);
   ReadArgs(lsm, argc, argv);
   PipeCells(lsm, &status);
   return status;
}
