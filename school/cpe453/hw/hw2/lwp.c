/* CPE453 - Assignment 2 - liblwp.so
 * Jared Spadaro, Section 3, Nico
 *
 * This library is intended for running and maintaining 
 * lightweight processes (lwp's).
 *
 * This assignment was done alone.
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "lwp.h"
#include "fp.h"

#define WORD_SIZE sizeof(unsigned long)
#define SAFE_STACK_SIZE 1024

void rr_admit(thread);
void rr_remove(thread);
thread rr_next(void);

/* global tid counter to account for all threads */
static unsigned long global_tid = 0;

/* global thread list head - starting point for thread list */
static thread global_head = NULL;

/* currently running thread */
static thread global_current = NULL;

/* context of system */
static thread global_maincontext = NULL;

/* safe stack to go to when destroying lwp */
static unsigned long *global_safestack = NULL;

/* default scheduler */
static struct scheduler rr_publish = {NULL, NULL, rr_admit, 
 rr_remove, rr_next}; 

static scheduler global_current_scheduler = NULL;

/* call this when we want to go to start of list of threads */
thread goto_start() {
   thread temp = global_head;
   if(!temp) {
      return NULL;
   }
   while(temp->lib_two) {
      temp = temp->lib_two;
   }
   return temp;
}

/* SCHEDULER FUNCTIONS */

/* add the passed context to the scheduler's scheduling pool */
void rr_admit(thread new) {
   if (!global_head) {
      new->lib_one = NULL; 
      new->lib_two = NULL;
   }
   else {
      global_head->lib_one = new;
      new->lib_two = global_head; 
      new->lib_one = NULL; 
   }
   global_head = new;    
}

/* remove the passed context from the scheduler's scheduling pool */
void rr_remove(thread victim) {
   if(victim->lib_one && victim->lib_two) { 
      (victim->lib_two)->lib_one = victim->lib_one;
      (victim->lib_one)->lib_two = victim->lib_two;
   }
   else if(victim->lib_one) { 
      (victim->lib_one)->lib_two = victim->lib_two;
   }
   else if(victim->lib_two) { 
      (victim->lib_two)->lib_one = victim->lib_one;
   }
   else {}
   free(victim->stack);
   free(victim);
}

/* return the next thread to run or NULL if there isn't one */
thread rr_next(void) {
   static int init = 1;
   thread temp = global_current;
   if(temp == NULL) { 
      if(!global_head) { 
         return NULL;
      }
      else if (init) { /* if init, then we are initializing system */
         temp = goto_start(); 
         init = 0;
      }
      else {
         return NULL;
      }
   } 
   else if(temp->lib_one == NULL) { 
      if(!temp->lib_two) { 
         temp = NULL;
      }
      else {
         temp = goto_start();
      }
   }
   else {
      temp = temp->lib_one;
   }
   return temp;        
}


/* creates a new lwp which executes the given function with the given argument.
 * the new processes' stack will be [stacksize] words.
 * returns the tid of the new thread, else -1
 */
tid_t lwp_create(lwpfun function, void *arg, size_t stack_size) {
   thread newthread = malloc(sizeof(context)); /* create new thread */   

   if(!global_current_scheduler) {
      lwp_set_scheduler(NULL);    
   }
   
   newthread->tid = ++global_tid; 
   newthread->stack = malloc(WORD_SIZE * stack_size); 
   newthread->stacksize = stack_size; 
   newthread->state.fxsave = FPU_INIT; 
   
   /* placing address of lwpfun and lwp_exit on stack */
   unsigned long *temp = newthread->stack + stack_size - 3; 
   newthread->state.rsp = newthread->state.rbp = (unsigned long)temp; 
   temp++;
   *temp = (unsigned long)function; 
   temp++; 
   *temp = (unsigned long)lwp_exit; 
   newthread->state.rdi = (unsigned long)arg; 
   global_current_scheduler->admit(newthread);
   return newthread->tid;
}

/* called from within exit, to allow for safe stack creation */
void freeThread() {
   thread temp = global_current;
   
   global_current = global_current_scheduler->next();
   if(temp) {
      global_current_scheduler->remove(temp);
   }
   temp = NULL;
 
   if (global_current == NULL) {
      lwp_stop();
   }
   load_context(&global_current->state);
}

/* terminates the current lwp and frees its resources. calls sched->next() to 
 * get new thread. if there are no other threads, calls lwp_stop()
 */
void lwp_exit(void) {
   if(!global_safestack) {
      global_safestack = malloc(WORD_SIZE * SAFE_STACK_SIZE);
   }
   /* set sp to somewhere other than current stack (end of global safe stack)*/
   SetSP(global_safestack + SAFE_STACK_SIZE); 
   freeThread();  
}


/* returns the tid of the calling lwp */
tid_t lwp_gettid(void) {
   return global_current->tid;
}


/* yields control to another lwp. which one depends on the scheduler.
 * saves the current lwp's context, picks the next one, restores that
 * thread's context, and returns
 */
void lwp_yield(void) {
   save_context(&global_current->state);
   if(!global_current->lib_two && !global_current->lib_one) {
      return;
   }
   global_current = global_current_scheduler->next();
   if(global_current == NULL) {
      lwp_stop();
   }
   load_context(&global_current->state);
}


/* starts lwp system. saves original context (used by lwp_stop), picks lwp 
 * using scheduler and starts it. if there are no lwp's to run, return 
 */
void lwp_start(void) {
   if(!global_maincontext) {
      global_maincontext = malloc(sizeof(context));
   }
   if(!global_current_scheduler) {
      lwp_set_scheduler(NULL);    
   }
   global_current = global_current_scheduler->next();
   if(global_current == NULL) {
      return;
   }
   swap_rfiles(&global_maincontext->state, &global_current->state);
}


/* stops the lwp system, restores the original stack pointer and
 * returns that context (wherever lwp_start was called from).
 * does not destroy any existing contexts, and thread processing
 * will be restarted by a call to lwp_start()
 */
void lwp_stop(void) {
   load_context(&global_maincontext->state);
}


/* causes the lwp package to use the given scheduler to choose the
 * next process to run. transfers all threads from the old scheduler
 * to the new one in "next()" order. if scheduler is NULL, or has
 * never been set, the scheduler should do round-robin scheduling
 */
void lwp_set_scheduler(scheduler new_scheduler) {
   if(!new_scheduler) {
      global_current_scheduler = &rr_publish;
      return;
   }
   if (new_scheduler->init != NULL) {
      new_scheduler->init();
   }
   if(global_current_scheduler) {
      thread temp = global_current_scheduler->next();
      while (temp) {
         new_scheduler->admit(temp);
         global_current_scheduler->remove(temp);
         temp = global_current_scheduler->next();
      }
      if (global_current_scheduler->shutdown != NULL) {
         global_current_scheduler->shutdown();
      }
   }
   global_current_scheduler = new_scheduler;
}


/* returns the pointer to the current scheduler */
scheduler lwp_get_scheduler(void) {
   return global_current_scheduler;
}


/* returns thread corresponding to given thread ID (else NULL) */
thread tid2thread(tid_t tid) {
   thread temp = goto_start();
   if (!temp) {
      return NULL;
   }
   while (temp->lib_one) {
      if (temp->tid == tid) {
         return temp;
      }
      temp = temp->lib_one;
   }
   return NULL;
}




