/** cpe453 - Lab 1 - pipeit
 *  This program executes the pipeline "ls | sort -r > outfile"
 *  Jared Spadaro
 *  Section 3
 *  9/27/16
 *  Nico
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUM_FORKS 2

void PipeIt () {
   int i, status[NUM_FORKS], outFD, childPID, pipeFDs[NUM_FORKS];
   pipe(pipeFDs);
   for (i = 0; i < NUM_FORKS; i++) {
      if ((childPID = fork()) < 0) {
         fprintf(stderr, "Error\n");
      }
      else if (childPID) { /* parent */
         if (i) {
            close(pipeFDs[0]); /* parent does not use pipe */
            close(pipeFDs[1]);
         }       
      }
      else { /* child */
         if (i == 0) { /* first child (ls) */
            close(pipeFDs[0]); 
            dup2(pipeFDs[1], 1); /* ls will now output to pipe */
            close(pipeFDs[1]); 
            execlp("ls", "ls", NULL);
         }
         else { /* second child (sort) */
            close(pipeFDs[1]);
            dup2(pipeFDs[0], 0); /* sort will now read from pipe */
            close(pipeFDs[0]); 
            outFD = open("outfile", O_WRONLY|O_CREAT|O_TRUNC, 0644); /* create output file */
            dup2(outFD, 1); /* sort will now output to outfile */
            close(outFD); 
            execlp("sort", "sort", "-r", NULL);
         }
      }
   }

   /* wait for children to execute */
   for (i = 0; i < NUM_FORKS; i++) {
      wait(&status[i]);
   }

   /* check to see if children exited successfully */   
   if (WIFEXITED(status[0]) && WIFEXITED(status[1])) {
      exit(EXIT_SUCCESS);
   }
   else {
      perror("Error");
      exit(EXIT_FAILURE);
   }
}

int main (void) {
   PipeIt();
   return 0;
}
