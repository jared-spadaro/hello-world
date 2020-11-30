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

#define MAX_IN 2
#define MAX_OUT 3
#define MAX_FD 12
#define REPORT_SIZE 16

typedef struct {
   int numSteps;    
   int inFDs[MAX_IN];   
   int numInFDs;
   int outFDs[MAX_OUT]; 
   int numOutFDs; 
   int isEnd;
   Report report;     
} Cell;

void initCell(Cell *c) {
   int i;
   c->numSteps = 0;
   for (i = 0; i < MAX_IN; i++) {
      c->inFDs[i] = 0;
   }
   c->numInFDs = 0;
   for (i = 0; i < MAX_OUT; i++) {
      c->outFDs[i] = 0;
   }
   c->numOutFDs = 0;
   c->isEnd = 0;

   c->report.id = 0;
   c->report.step = 0;
   c->report.value = 0;
}

int checkArg(char **args, int ndx, char arg) {
   int rtn = 0;
   if (args[ndx][0] == arg) {
      if (args[ndx][1] && isdigit(*(args[ndx]+1))) {
         rtn = 1;
      }
   }
   else {
      rtn = 0;
   }
   return rtn;
}

void ReadArgs (Cell *c, int numArgs, char **args) {
   int i, curr;
   for (i = 1; i < numArgs; i++) { //skip 0 since it will be name of executable
      if (checkArg(args, i, 'S')) {
         c->numSteps = strtol(args[i]+1, NULL, 10);
         //printf("Number of steps = %d\n", c->numSteps);
      }
      else if (checkArg(args, i, 'O')) {
         curr = strtol(args[i]+1, NULL, 10);
         if (curr > MAX_FD) {
            //printf("File descriptor too large\n");
         }
         else {
            c->outFDs[c->numOutFDs] = curr;
            c->numOutFDs++;
            //printf("Output file descriptor = %d\n", c.outFDs[c.numOutFDs++]);
         }
      }
      else if (checkArg(args, i, 'I')) {
         curr = strtol(args[i]+1, NULL, 10);
         if (curr > MAX_FD) {
            //printf("File descriptor too large\n");
         }
         else {
            c->inFDs[c->numInFDs] = curr;
            c->numInFDs++;
            //printf("Input file descriptor = %d\n", c.inFDs[c.numInFDs++]);
         }
      }
      else if (checkArg(args, i, 'D')) {
         c->report.id = strtol(args[i]+1, NULL, 10);
         //printf("Unique ID = %d\n", c.report.id);
      }
      else if (checkArg(args, i, 'V')) {
         c->isEnd = 1;
         c->report.value = atof(args[i]+1);
         //printf("Fixed value = %.3lf\n", c.report.value);
      }
      else {
         //printf("Bad argument (ignored)\n");
      }
   }
} 
    
void ReadReports (Report *inReports, Cell *c, int currentStep) {
   int i, bytesRead, inFD;
   for (i = 0; i < c->numInFDs; i++) {
      inFD = c->inFDs[i];
      bytesRead = read(inFD, &inReports[i], sizeof(Report));
      if (bytesRead < sizeof(Report)) {
         exit(EXIT_FAILURE);
      }
   }   
} 

void AverageReports(Cell *c, Report *inReports) {
   int i;
   c->report.value = 0;
   for (i = 0; i < c->numInFDs; i++) {
      c->report.value += inReports[i].value;
   }
   if(c->report.value) {
      c->report.value /= c->numInFDs;
   }
}

void WriteReports (Cell *c) {
   //printf("in: write reports function (Cell ID = %d)\n", c->report.id);
   int i, bytesWritten, outFD;
   for (i = 0; i < c->numOutFDs; i++) {
      outFD = c->outFDs[i];
      bytesWritten = write(outFD, &c->report, sizeof(Report));
      /*if(bytesWritten != REPORT_SIZE) {
         exit(EXIT_FAILURE);
      }
      else if (bytesWritten == -1) {
         perror("write");
         exit(EXIT_FAILURE);
      }
      else {
         exit(EXIT_FAILURE);
      }*/
   }
}                                                 

void printReport (Cell *c, Report *r) {
   printf("Report ID = %d\n", r->id);
   printf("Report step = %d\n", r->step);
   printf("Report value = %.3lf\n", r->value);
}

void printCell (Cell *c) {
   int i;
   printf("[Cell %d] Num steps = %d\n", c->report.id, c->numSteps);    
   printf("[Cell %d] NumInFDs = %d\n", c->report.id, c->numInFDs);
   for (i = 0; i < c->numInFDs; i++) {
      printf("[Cell %d] inFD[%d] = %d\n", c->report.id, i, c->inFDs[i]);
   }
   printf("[Cell %d] NumOutFDs = %d\n", c->report.id, c->numOutFDs);
   for (i = 0; i < c->numOutFDs; i++) {
      printf("[Cell %d] outFD[%d] = %d\n", c->report.id, i, c->outFDs[i]);
   }   
   printf("[Cell %d] Report step = %d\n", c->report.id, c->report.step);
   printf("[Cell %d] Report value = %.3lf\n", c->report.id, c->report.value);
}    
   
void closeFDs (Cell *c) {
   int i;
   for (i = 0; i < c->numOutFDs; i++) {
      close(c->outFDs[i]);
   }
   for (i = 0; i < c->numInFDs; i++) {
      close(c->inFDs[i]);
   }
}

void Simulate (Cell *c) {
   int i;
   //printf("Entered simulate function\n");
   //printf("Numsteps = %d\n", c->numSteps);
   Report *inReports = calloc(c->numInFDs, sizeof(Report));
   for (i = 0; i <= c->numSteps; i++) {
      //printf("in loop of sim func\n");
      //ReadReports(inReports, c, i);
      //AverageReports(c, inReports);
      //printCell(c);
      WriteReports(c);
      ReadReports(inReports, c, i);
      if(!c->isEnd) {
          AverageReports(c, inReports);
      }
      c->report.step++;
   }
   //closeFDs(c);
   //WriteReports(c);
}

void printCmdline (int numArgs, char **args) {
   int i;
   for(i = 0; i < numArgs; i++) {
      printf("%s ", *args++);
   }
   printf("\n");
}


int main (int argc, char **argv) {
   //printf("Entered main of cell\n");
   Cell *c = calloc(sizeof(Cell), 1);
   //printf("Size of cell = %d, size of cell struct = %d\n", sizeof(*c), sizeof(Cell));
   initCell(c);
   //printf("After init Cell\n");
   //printCmdline(argc, argv);
   ReadArgs(c, argc, argv);
   //printCell(c);
   //printf("Address of cell = %d\n", c);
   //printf("Address of report in cell = %d\n", &c->report);
   //c->report.step = 21; 
   //Report *inReports = calloc(c->numInFDs, sizeof(Report));
   //ReadReports(inReports, c, 5);
   //printReport(inReports);
   //WriteReports(c);
   //AverageReports(c, inReports);
   Simulate(c);
   exit(EXIT_SUCCESS);
   return 0;
}  
