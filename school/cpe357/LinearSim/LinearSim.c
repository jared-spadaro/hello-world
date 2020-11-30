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
#define MAX_NUM_ARGS 10
#define MAX_CELLS 50
#define MAX_OUT_FDS 3
#define MAX_IN_FDS 2


typedef struct {
   int numCells;
   int numSteps;
   double left;
   double right;
} LinearSim;

void initLS (LinearSim *ls) {
   ls->numCells = 0;
   ls->numSteps = 0;
   ls->left = 0;
   ls->right = 0;
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
   for (i = 1; i < numArgs; i++) { //skip 0 since it will be name of executable
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
         else {
            l = -1;
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
         else {
            r = -1;
         }
      }
      else {

      }
   }
   if((ls->numCells < 2 && r)|| !c || !s) {
      printf("Usage: LinearSim C S L R (in any order)\n");
      exit(EXIT_FAILURE);
   }   
}

void printLS (LinearSim *ls) {
   printf("NumCells = %d\n", ls->numCells);
   printf("NumSteps = %d\n", ls->numSteps);
   printf("Left value = %.3lf\n", ls->left);
   printf("Right value = %.3lf\n", ls->right);
}

void genCellCmd(char *cmd, int numSteps, int numOut, int *outFDs, int numIn, int *inFDs, double value, int ID) {
   int i;
   char *temp = calloc(sizeof(char), 5);
   sprintf(cmd, "S%d ", numSteps);

   for (i = 0; i < numOut; i++) {
      sprintf(temp, "O%d ", *(outFDs + i));
      strcat(cmd, temp);
   }

   for (i = 0; i < numIn; i++) {
      sprintf(temp, "I%d ", *(inFDs + i));
      strcat(cmd, temp);
   }

   if (value) {
      sprintf(temp, "V%lf ", value);
      strcat(cmd, temp);
   }

   sprintf(temp, "D%d ", ID);
   strcat(cmd, temp);
}

void parseCmd (char *oldCmd, int numArgs, char **newCmd) {
   int i;
   newCmd[0] = "./Cell";
   newCmd[1] = strtok(oldCmd, " ");
   for (i = 2; i <= numArgs; i++) {
      newCmd[i] = strtok(NULL, " ");
   }
   for (i = 0; i <= numArgs; i++) {
      printf("%s ", newCmd[i]);
   }
   printf("\n");
}


void pipeCells(LinearSim *ls) {
   int childPIDs[MAX_CELLS];
 
   int outFDs[MAX_OUT_FDS] = {0, 0, 0};
   int inFDs[MAX_IN_FDS] = {0, 0};
  
   int numArgs, currCell, childPID;
   int mainFDs[2];                   //used by all Cells to write back to LinearSim
   int toNextFDs[2];                 //used to write to next cell / read from prev cell
   int fromNextFDs[2];               //used to read from next cell / write to prev cell
   int inFD = -1, outFD = -1;        //these will be used to save pipe FDs for use by next Cell
   int oldIn = -1, oldOut = -1;      //these are legacy fds that need to be saved to preserve pipes, and later closed
   char *cmd = calloc(sizeof(char), MAX_CMD_LENGTH);
   char **goodCmd = calloc(sizeof(char *), MAX_NUM_ARGS);
   int numIn = 0, numOut = 0;  

   pipe(mainFDs);                    //set up pipe b/w LS and all cells
   int numCells = ls->numCells;
   for (currCell = 0; currCell < numCells; currCell++) {
      numArgs = 6; //minimum number of args e.g. "./Cell SN ON ON VX DN" 
      if (currCell == 0) {
         pipe(toNextFDs);          //pipe from Cell 0 to Cell 1
      }
      else if (currCell > 0 && currCell < numCells - 2) {
         //printf("entered if on second run\n");
         pipe(fromNextFDs); //fds 7 and 8 (5 and 6)
         pipe(toNextFDs); //fds 9 and 10  (11 and 12)
      }
      else if (currCell == numCells - 2) {
         //printf("entered second to last cell check before fork\n");
         pipe(fromNextFDs);
      }
      else {  //rightmost cell
 
      }
      if ((childPID = fork()) < 0) {   
         perror("fork");
         exit(EXIT_FAILURE);
      }
      else if (childPID) {           //parent
         childPIDs[currCell] = childPID;
         //printf("child pid = %d\n", childPIDs[currCell]);
         if (currCell == 0) {        //open fds: 3, 4, 5, 6
            //close(mainFDs[1]);     
            inFD = toNextFDs[0];     //next child will read this (fd 5)
            oldOut = toNextFDs[1];   //must be kept open for now 
            //close(toNextFDs[1]); MUSt remain open to allow next cell to read! I think...  
         }
         else if (currCell > 0) {
            //printf("entered parent, second run\n");
            //open fds: 3, 4, 5, 6, 7, 8, 9, 10
            if (oldOut > 0) {
               close(oldOut); //in this case, fd 6, whose pipe is not needed by Cell 2
            }
            //open fds: 3, 4, 5, 7, 8, 9, 10
            if (oldIn > 0) {
               close(oldIn); //in this case, nothing
            }
            if (inFD > 0) {
               close(inFD);  //in this case, fd 5, whose pipe is not needed by Cell 2
            }
            //open fds: 3, 4, 7, 8, 9, 10
            if (outFD > 0) {
               close(outFD);  //in this case, nothing
            }

            if (currCell < numCells - 1) {
               inFD = toNextFDs[0];     //fd 9
               outFD = fromNextFDs[1];  //fd 8
               oldIn = fromNextFDs[0];  //fd 7
               oldOut = toNextFDs[1];   //fd 10
            }
            else { //final clean up, after forking off last cell
               close(fromNextFDs[0]);
               close(fromNextFDs[1]); 
            }
               
            
         }
         /*else if (currCell == numCells - 2) {
            
         }*/
         else {  //rightmost cell
            
         }
         //printf("end of parent run #%d\n", currCell);
      }
      else {                        //child
         close(mainFDs[0]);
         outFDs[0] = mainFDs[1];
         if (currCell == 0) {
            //open fds: 4, 5, 6
            //close(toNextFDs[0]);   //open fds: 4, 6
            outFDs[1] = toNextFDs[1];
            genCellCmd(cmd, ls->numSteps, MAX_OUT_FDS-1, outFDs, 0, inFDs, ls->left, currCell);
            parseCmd(cmd, numArgs, goodCmd);      
            //execv(goodCmd[0], goodCmd);
            //printf("print after prsecmd\n");
            exit(0);
         }
         else if (currCell > 0 && currCell < numCells - 2) {
            //open fds: 4, 5, 6, 7, 8, 9, 10
            numArgs++;

            outFDs[1] = toNextFDs[1];    //fd 10 (12)
            if (currCell > 1) {
               outFDs[2] = outFD;        //fd 8
               numArgs++;
            }
            inFDs[0] = inFD;             //fd 5  (9)
            inFDs[1] = fromNextFDs[0];   //fd 7  (5)
            
            if(currCell == 1) {
               numOut = MAX_OUT_FDS - 1;
            }
            else {
               numOut = MAX_OUT_FDS;
            }
            numIn = MAX_IN_FDS;
            genCellCmd(cmd, ls->numSteps, numOut, outFDs, numIn, inFDs, 0, currCell);
            parseCmd(cmd, numArgs, goodCmd);
            //execv(goodCmd[0], goodCmd); 
            exit(0);
         }
         else if (currCell == numCells - 2) {
            numArgs++;
            inFDs[0] = inFD;            //fd 11
            inFDs[1] = fromNextFDs[0];  //fd 7
            outFDs[1] = outFD;          //fd 6
            numOut = MAX_OUT_FDS - 1;
            numIn = MAX_IN_FDS;
            genCellCmd(cmd, ls->numSteps, numOut, outFDs, numIn, inFDs, 0, currCell);
            parseCmd(cmd, numArgs, goodCmd);
            //execv(goodCmd[0], goodCmd);
            exit(0);
         }
         else {  //rightmost cell
           numArgs = 6;
           outFDs[1] = fromNextFDs[1];
           numOut = MAX_OUT_FDS - 1;
           numIn = 0;
           genCellCmd(cmd, ls->numSteps, numOut, outFDs, numIn, inFDs, ls->right, currCell);
           parseCmd(cmd, numArgs, goodCmd);
           //execv(goodCmd[0], goodCmd);
           exit(0);
         }     
      }
   }
   for (currCell = 0; currCell < numCells; currCell++) {
      wait(NULL);
   }
}


int main (int argc, char **argv) {
   LinearSim *ls = calloc(sizeof(LinearSim), 1);
   initLS(ls);
   ReadArgs(ls, argc, argv);
   //printLS(ls);
   pipeCells(ls);

   /*char *cmd = calloc(sizeof(char), MAX_CMD_LENGTH);
   int outFDs[3] = {4, 6, 8};
   int inFDs[2] = {3, 5};
   genCellCmd(cmd, 4, 1, outFDs, 2, inFDs, 0, 7);
   printf("Cell Command = %s\n", cmd);*/

   //char **newCmd = calloc(sizeof(char *), 10);
   //parseCmd(cmd, 6, newCmd);

   

   return 0;
}







