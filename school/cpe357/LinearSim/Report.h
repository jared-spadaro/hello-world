#ifndef REPORT_H
#define REPORT_H

typedef struct {
   int id;         //ID of Cell reporting
   int step;       //Time for which report is being made
   double value;   //Value of cell at time "step"
} Report;

#endif
