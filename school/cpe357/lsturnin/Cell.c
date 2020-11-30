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
#define BASE_TEN 10
#define STEP 'S'
#define OUT 'O'
#define IN 'I'
#define ID 'D'
#define VALUE 'V'

typedef struct {
   int numSteps;    
   int inFDs[MAX_IN];   
   int numInFDs;
   int outFDs[MAX_OUT]; 
   int numOutFDs;
 
   int isEnd;
   Report report;     
} Cell;

void InitCell(Cell *cell) {
   int ndx;

   cell->numSteps = 0;
   for (ndx = 0; ndx < MAX_IN; ndx++) {
      cell->inFDs[ndx] = 0;
   }
   cell->numInFDs = 0;
   for (ndx = 0; ndx < MAX_OUT; ndx++) {
      cell->outFDs[ndx] = 0;
   }

   cell->numOutFDs = 0;
   cell->isEnd = 0;
   cell->report.id = 0;
   cell->report.step = 0;
   cell->report.value = 0;
}

int CheckArg(char **args, int ndx, char arg) {
   int rtn = 0;
   int offset = 1;

   if (args[ndx][0] == arg) {
      if (args[ndx][1] && *(args[ndx] + 1) == '-') {
         offset++;
      }
      if (args[ndx][1] && *(args[ndx] + 1) == '.') {
         offset++;
      }
      if (args[ndx][offset] && isdigit(*(args[ndx] + offset))) {
         rtn = 1;
      }
   }
   else {
      rtn = 0;
   }

   return rtn;
}

void ReadArgs(Cell *cell, int numArgs, char **args) {
   int ndx, curr;

   for (ndx = 1; ndx < numArgs; ndx++) { 
      if (CheckArg(args, ndx, STEP)) {
         cell->numSteps = strtol(args[ndx] + 1, NULL, BASE_TEN);
      }
      else if (CheckArg(args, ndx, OUT)) {
         curr = strtol(args[ndx] + 1, NULL, BASE_TEN);
         if (curr > MAX_FD) {
            exit(EXIT_FAILURE);
         }
         else {
            cell->outFDs[cell->numOutFDs] = curr;
            cell->numOutFDs++;
         }
      }
      else if (CheckArg(args, ndx, IN)) {
         curr = strtol(args[ndx] + 1, NULL, BASE_TEN);
         if (curr > MAX_FD) {
            exit(EXIT_FAILURE);
         }
         else {
            cell->inFDs[cell->numInFDs] = curr;
            cell->numInFDs++;
         }
      }
      else if (CheckArg(args, ndx, ID)) {
         cell->report.id = strtol(args[ndx] + 1, NULL, BASE_TEN);
      }
      else if (CheckArg(args, ndx, VALUE)) {
         cell->isEnd = 1;
         cell->report.value = atof(args[ndx] + 1);
      }
      else { 
      }
   }
} 
    
void ReadReports(Report *inReports, Cell *cell) {
   int ndx, bytesRead, inFD;

   for (ndx = 0; ndx < cell->numInFDs; ndx++) {
      inFD = cell->inFDs[ndx];
      bytesRead = read(inFD, &inReports[ndx], sizeof(Report));

      if (bytesRead < sizeof(Report)) {
         exit(EXIT_FAILURE);
      }
   }   
} 

void AverageReports(Cell *cell, Report *inReports) {
   int ndx;

   cell->report.value = 0;
   for (ndx = 0; ndx < cell->numInFDs; ndx++) {
      cell->report.value += inReports[ndx].value;
   }
   if (cell->report.value) {
      cell->report.value /= cell->numInFDs;
   }
}

void WriteReports(Cell *cell) {
   int ndx, bytesWritten, outFD;

   for (ndx = 0; ndx < cell->numOutFDs; ndx++) {
      outFD = cell->outFDs[ndx];
      bytesWritten = write(outFD, &cell->report, sizeof(Report));
   }
}                                                 

void CloseFDs(Cell *cell) {
   int ndx;

   for (ndx = 0; ndx < cell->numOutFDs; ndx++) {
      close(cell->outFDs[ndx]);
   }
   for (ndx = 0; ndx < cell->numInFDs; ndx++) {
      close(cell->inFDs[ndx]);
   }
}

void Simulate(Cell *cell) {
   int ndx;
   Report *inReports = calloc(cell->numInFDs, sizeof(Report));

   for (ndx = 0; ndx <= cell->numSteps; ndx++) {
      WriteReports(cell);
      ReadReports(inReports, cell);

      if (!cell->isEnd) {
         AverageReports(cell, inReports);
      }
      cell->report.step++;
   }
}

void PrintCmdLine(int numArgs, char **args) {
   int ndx;

   for (ndx = 0; ndx < numArgs; ndx++) {
      printf("%s ", *args++);
   }
   printf("\n");
}

int main(int argc, char **argv) {
   Cell *cell = calloc(sizeof(Cell), 1);

   InitCell(cell);
   ReadArgs(cell, argc, argv);
   Simulate(cell);
   exit(EXIT_SUCCESS);
   return 0;
}  
