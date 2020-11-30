#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "SmartAlloc.h"
#include "CodeSet.h"

//stores info for code; getCode will create new code and take info from CodeEntry
typedef struct CodeEntry {
   unsigned char *data;
   unsigned short size;
} CodeEntry;

typedef struct CodeSet {
   CodeEntry *CodeEntries;
   int maxNumCodes;
   int index;
} CodeSet;


void *CreateCodeSet (int numCodes) {
   CodeSet *cs = malloc(sizeof(CodeSet));
   cs -> CodeEntries = malloc(sizeof(CodeEntry) * numCodes);
   cs -> maxNumCodes = numCodes;
   cs -> index = 0;  
   return cs;
}


int NewCode (void *codeSet, char val) {
   CodeSet *cs = (CodeSet *)codeSet;                  //pointer to CodeSet
   CodeEntry *ce = cs -> CodeEntries + cs -> index;   //pointer to CodeEntry at current index
   ce -> data = malloc(sizeof(char));                 //allocate memory for code (and initialize data pointer!)
   *(ce -> data) = val;                               //assign value to code
   ce -> size = 1;
   return (cs -> index)++;                            //return current index then increment
}


int ExtendCode (void *codeSet, int oldCode) {
   CodeSet *cs = (CodeSet *)codeSet;
   CodeEntry *old = cs -> CodeEntries + oldCode;         //CodeEntry for code that we are extending (want to extract data and size)
   CodeEntry *new = cs -> CodeEntries + cs -> index;     //new CodeEntry at current index, which will extend "old"
   new -> data = malloc(old -> size + 1);                        //size of extended code is old code + 1 for 0 byte  
   memcpy(new -> data, old -> data, old -> size);     //copies old code into new code (still need to add 0 byte)
   *(new -> data + old -> size) = '\0';                  //make the last byte NULL aka '\0' aka 0 value
   new -> size = old -> size + 1;                        //size of new code is size of old code + 1
   return (cs -> index)++;                               //return current index then increment
}


void SetSuffix (void *codeSet, int code, char suffix) {
   CodeSet *cs = (CodeSet *)codeSet;
   CodeEntry *ce = cs -> CodeEntries + code;            //access CodeEntry at given index
   *(ce -> data + ce -> size - 1) = suffix;             //set last byte of data to given suffix
}


Code GetCode (void *codeSet, int code) {
   CodeSet *cs = (CodeSet *)codeSet;
   CodeEntry *ce = cs -> CodeEntries + code;
   Code c;
   c.data = ce -> data;                             
   c.size = ce -> size;
   return c;   
}


void FreeCode (void *codeSet, int code) {
   /*CodeSet *cs = (CodeSet *)codeSet;
   CodeEntry *ce = cs -> CodeEntries + code;
   free(ce -> data);*/
}


void DestroyCodeSet (void *codeSet) {
   CodeSet *cs = (CodeSet *)codeSet;
   CodeEntry *ce = cs -> CodeEntries;    //gives pointer to first CodeEntry 
   int numCodes = cs -> index;
   while(numCodes--) {                   //free each data block
      free((ce + numCodes) -> data);
   }
   free(cs -> CodeEntries);              //free block of CodeEntries
   free(cs);                             //free CodeSet itself
}



