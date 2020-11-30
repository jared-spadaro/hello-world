/* CSC453 - Assignment 1 - malloc library
 * Jared Spadaro
 * Section 03, Nico, 10/6/16
 * This program is a library which mimics stdlib
 * functions malloc, calloc, realloc, and free.
 * NOTE: realloc not implemented
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define BLK_SIZE 64000
#define HEADER_SIZE sizeof(MemBlock)
#define BUFFER_MULTIPLIER 3

/* struct containing metadat of memory blocks */
typedef struct MemBlock {
   int size; 
   int isFree; 
   int magic; /* use for debugging, pads struct to 16 bytes */
   struct MemBlock *next; 
} MemBlock;

/* constant for checking environment variable of same name */
static const char *debug = "DEBUG_MALLOC";

/* static global variables for keeping track of memory */
static void *globalOriginalBreak = NULL;
static void *globalCurrentBreak = NULL;
static MemBlock *globalLast = NULL;

/* ask OS for more memory via sbrk */
MemBlock *pushBreak(size_t size) {
   MemBlock *newBlk;
   char *nextLocation;
   size_t sbrkSize;
   
   if (size > BLK_SIZE) {
      sbrkSize = size;
   }
   else {
      sbrkSize = BLK_SIZE;
   }

   newBlk = sbrk(BLK_SIZE);
   if(newBlk == (void *)-1) {
      perror("Sbrk(2) error");
      return NULL;
   }
   if (globalLast) { 
      globalLast->next = newBlk;
   }

   /* next mem block will be "size" bytes away */
   nextLocation = (char *)newBlk + size; 
   newBlk->next = (MemBlock *)nextLocation;
   newBlk->size = size;
   newBlk->isFree = 0;
   return newBlk;
}

/* check the heap for suitable blocks of free memory */
MemBlock *SearchForFreeSpace(size_t size) {
   MemBlock *temp = (MemBlock *)(globalOriginalBreak);
   while (temp->next) {
      if (temp->isFree && temp->size >= size) {
         return temp;
      }
      temp = temp->next;
   }
   return NULL;
}

/* ensure that the size we have is divisible by 16 */
void CheckSize(size_t *size) {
   if((*size) % 16 != 0) {
      (*size)++;
      CheckSize(size);
   }
}

/* ensure that the program break is divisible by 16 */
void CheckBreakLocation() {
   size_t oldBreak, newBreak;
   newBreak = oldBreak = (size_t)sbrk(0);
   CheckSize(&newBreak);
   sbrk(newBreak - oldBreak);
}


/* check to see if there is room in the heap for a new memory block */
int TestHeap(size_t size) {
   int usedSpace, remainingSpace;
   MemBlock *newBlk = globalLast->next; /*point to end of allocated memory */
   char *charCurrentBreak = (char *)globalCurrentBreak;
   char *charLast = (char *)newBlk;
   usedSpace = charLast - charCurrentBreak;
   remainingSpace = BLK_SIZE - usedSpace;
   return remainingSpace >= size; 
}

/* add memory block to heap. called after we confirm that there are 
 * no "free" slots to use (ie, chunks that have been allocated and 
 * then freed) but there is unused heap space */
MemBlock *AddBlock(size_t size) {
   MemBlock *newBlk;
   char *nextLocation;
   newBlk = globalLast->next; 
   newBlk->size = size;
   newBlk->isFree = 0;
      
   nextLocation = (char *)newBlk + size;
   newBlk->next = (MemBlock *)nextLocation;    
   return newBlk; 
}

/* search the heap to see which memory block contains the given pointer.
 * called by free and realloc */ 
MemBlock *FindBlock(void *ptr) {
   MemBlock *temp = globalOriginalBreak, *key = ptr;
   if (key < temp) {
      return NULL;
   }
   while (temp->next) {
      if (key >= temp && key < temp->next) {
         return temp;
      }
      temp = temp->next;
   }
   return NULL;
}

/* mark the memory block containing the given pointer as free */
void free (void *ptr) {
   if (!ptr) {
      return; 
   }
   MemBlock *toFree = FindBlock(ptr);
   if (!toFree) {
      fputs("Error: Free: invalid pointer", stderr);
   }
   else {
      /* merge adjacent free blocks */
      if (toFree->next->isFree) {
         toFree->size = toFree->size + toFree->next->size; 
         char *charNext = (char *)toFree->next;
         charNext += toFree->next->size;
         toFree->next = (MemBlock *)charNext;
      }
      toFree->isFree = 1;
   }
   /* check environment variable for debugging */
   if (getenv(debug)) {
      char *format = "MALLOC: free(%p)\n";
      int strLen = strlen(format) * BUFFER_MULTIPLIER;
      char dest[strLen];
      snprintf(dest, strLen, format, toFree);
      fputs(dest, stderr);
   }
}    

/* allocate "size" bytes and return pointer to them */
void *malloc(size_t size) {
   if (size <= 0) {
      return NULL;
   }
   MemBlock *newBlk;

   CheckBreakLocation();
   CheckSize(&size);
   size += HEADER_SIZE;   
   /* if globalLast is null, we must initialize program break */
   if (!globalLast) {
      newBlk = pushBreak(size);
      globalOriginalBreak = globalCurrentBreak = newBlk;
   }
   else if (NULL != (newBlk = SearchForFreeSpace(size))) {  
      newBlk->isFree = 0;
   }
   else if (TestHeap(size)) { /* if there is room in current heap */
      newBlk = AddBlock(size);
   }
   else { /* no free space, no room in heap, so we must push break */
      newBlk = globalCurrentBreak = pushBreak(size);
   }
   globalLast = newBlk; /* last now represents most recently created blk */  
   /* check environment variable for debugging */
   if (getenv(debug)) {
      char *format = "MALLOC: malloc(%d)    =>  (ptr=%p, size=%d)\n";
      int strLen = strlen(format) * BUFFER_MULTIPLIER;
      char dest[strLen];
      snprintf(dest, strLen, format, size - HEADER_SIZE, newBlk + 1, 
       size - HEADER_SIZE);
      fputs(dest, stderr);
   }
   return newBlk + 1; /* return pointer to beginning of user memory */
}

/* allocate (type x size) bytes, initialized to 0, and return pointer
 * to them */
void *calloc(size_t type, size_t size) {
   size_t mallocSize = type * size;
   char *mallocPtr = malloc(mallocSize);
   memset(mallocPtr, 0, mallocSize); /*initialize bytes to 0 */
   /*check environment variable for debugging */
   if (getenv(debug)) {
      char *format = "MALLOC: calloc(%d, %d)  =>  (ptr=%p, size=%d)\n";
      int strLen = strlen(format) * BUFFER_MULTIPLIER;
      char dest[strLen];
      snprintf(dest, strLen, format, type, size, mallocPtr, mallocSize); 
      fputs(dest, stderr);
   }
   return mallocPtr;
}

/* allocate size bytes at location pointer to by pointer.
 * **NOT IMPLEMENTED** */
void *realloc(void *ptr, size_t size) {
   if (!ptr) {
      return malloc(size);
   }
   else if (!size) {
      free(ptr);
      return NULL;
   }
   else if (size < 0) {
      return NULL;
   }
   else {
      /* actual realloc (ran out of time) */   
   }
   /* check environment variable for debugging */
   if (getenv(debug)) {
      char *format = "MALLOC: realloc(%p, %d)  =>  (ptr=%p, size=%d)\n";
      int strLen = strlen(format) * BUFFER_MULTIPLIER;
      char dest[strLen];
      snprintf(dest, strLen, format, ptr, size, ptr, size); 
      fputs(dest, stderr);
   }
   return NULL;
}

