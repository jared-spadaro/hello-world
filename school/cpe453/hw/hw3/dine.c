/* This program attempts to solve the dining philosophers problem.
 * Assignment 3, Section 3, Jared Spadaro
 * 10/31/2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

#define HUNGRY 0
#define CHANGING_AND_HUNGRY 1
#define EATING 2
#define CHANGING_AND_FULL 3
#define THINKING 4

#define AVAILABLE 0
#define USED 1

static pthread_mutex_t mutex;

typedef struct phil {
   int forks[2];        /* these are the two forks available to the philosopher. 
                         * use to index into "forks" array */
   int id;              /* this is the number which identifies which philosopher this is */
   int state;           /* this is the number telling us which state our philosopher is in */
   int *fork_state;     /* points to the state of the forks, located in "dine" */
   int numforks;        /* how many forks this philosopher has possession of (0, 1, or 2) */
   int waiting;         /* indicated whether this philosopher is waiting on a fork to be released */
   pthread_t thread;
} phil;

void *run_philosopher (void *info) {
   phil *meta = (phil *)info;
   /* Check if this philosopher's forks are available. Pick up any available forks.
    * Even philosophers try to pick up righthand fork first.
    * Odd philosophers try to pick up lefthand fork first.
    */
   int id = meta->id;
   int ndx1 = meta->forks[0];
   int ndx2 = meta->forks[1];
   int *fork_state = meta->fork_state;

   if(meta->state == HUNGRY) {
      if(id % 2 == 0) { /* if philosopher is "even" */
         /* Check if this fork is available. if it is, mark as USED.
          * On first check, if successful, return. 
          * We are only allowed to pick up one fork at a time.
          * On second check, if successful, change state to EATING.
          * If we check for an available fork and there is none, 
          * parent process will block until the proper fork(s) 
          * become available.
          */
         /* If desired fork is available, set to USED and increase numforks */
         if(fork_state[ndx1] == AVAILABLE) {
            //print line
            fork_state[ndx1] = USED;
            meta->numforks = 1;
            meta->state = CHANGING_AND_HUNGRY;
         }
      }
      else { /* philosopher is "odd" */
         /* If desired fork is available, set to USED and increase numforks */
         if(fork_state[ndx2] == AVAILABLE) {
            //print line
            fork_state[ndx2] = USED;
            meta->numforks = 1;
            meta->state = CHANGING_AND_HUNGRY;
         /* If desired fork is available, set to USED and increase numforks. 
          * Making this an else if because we can only pick up one fork at a time.
          */ 
         }
      }
   }
   else if(meta->state == CHANGING_AND_HUNGRY) {
      if(id % 2 == 0) { /* if philosopher is "even" */
         if(fork_state[ndx2] == AVAILABLE) {
            /* print line */
            fork_state[ndx2] = USED;
            meta->numforks = 2;
            meta->state = EATING;
         }
      }
      else {  /* if philosopher is "odd" */
         if(fork_state[ndx1] == AVAILABLE) {
            /* print line */
            fork_state[ndx1] = USED;
            meta->numforks = 2;
            meta->state = EATING;
         }
      }
   }
   else if(meta->state == EATING) {
      pthread_mutex_lock(&mutex);
      /* print line and delay */
      /* release one fork */
      fork_state[ndx1] = AVAILABLE;
      meta->numforks = 1;   
      meta->state = CHANGING_AND_FULL;
      pthread_mutex_unlock(&mutex);
   }
   else if(meta->state == CHANGING_AND_FULL) {
      /* print line and delay */
      /* release one fork */
      fork_state[ndx2] = AVAILABLE;
      meta->numforks = 0;
      meta->state = THINKING;
   }
   /* THINKING */
   else {
      /* print line and delay */
      /* either exit or repeat cycle */
   }
   return NULL;
}

/* set up array of philosophers with:
 * 1. the 2 forks available to them (initialized to AVAILABLE)
 * 2. their id (A, B, C, ...) (if >26, A+i, B+i, C+i...)
 * 3. their state (initialized to CHANGING_AND_HUNGRY)
 */
void init_philosophers (phil *philosophers, int *fork_status) {
   int i;
   for (i = 0; i < NUM_PHILOSOPHERS; i++) {
      (philosophers+i)->id = 'A' + i;  /* A, B, C, ... Z, then A+i, B+i, ... Z+i */ 
      (philosophers+i)->state = HUNGRY;
      (philosophers+i)->forks[0] = i;
      /* if we are initialized the last philosopher, his second fork must be the same as
       * the first philosopher's first fork */ 
      if(i < NUM_PHILOSOPHERS - 1) {
         (philosophers+i)->forks[1] = i+1;
      }
      else {
         (philosophers+i)->forks[1] = 0;
      }
      /* gives location of status of forks (in "dine") */
      (philosophers+i)->fork_state = fork_status;
      (philosophers+i)->numforks = 0;
      (philosophers+i)->waiting = 2; /* all philosophers are waiting on 2 forks to start */
   }
}

void dine(void) {
   int fork_status[NUM_PHILOSOPHERS] = {AVAILABLE};
   phil philosophers[NUM_PHILOSOPHERS];
   pthread_mutex_init(&mutex, NULL);
   init_philosophers(philosophers, fork_status);
   int i;
   pthread_mutex_init(&mutex, NULL);
   for (i = 0; i < NUM_PHILOSOPHERS; i++) {
      pthread_create(&philosophers[i].thread, NULL, run_philosopher, &philosophers[i]);                 
   } 
   for (i = 0; i < NUM_PHILOSOPHERS; i++) {
      pthread_join(philosophers[i].thread, NULL);
   }
}  
 

int main (void) {
   dine();
   return 0;
}


