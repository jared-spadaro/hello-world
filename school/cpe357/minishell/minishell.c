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

#define MAX_WORD_LEN 100
#define WORD_FMT "%100s"

/* One argument in a commandline (or the command itself) */
typedef struct Arg {
   char value[MAX_WORD_LEN+1];
   struct Arg *next;
} Arg;

/* One full command: executable, args and any file redirects */
typedef struct Command {
   int numArgs;    //Number of args including executable name
   Arg *args;      //Actual list of args
   char inFile[MAX_WORD_LEN+1];
   char outFile[MAX_WORD_LEN+1];
   struct Command *next;
} Command;

/* Make a new Arg, containing "str" */
static Arg *NewArg(char *str) {
   Arg *rtn = malloc(sizeof(Arg));

   strncpy(rtn->value, str, MAX_WORD_LEN);
   rtn->next = NULL;

   return rtn;
}

/* Make a new Command, with just the executable "cmd" */
static Command *NewCommand(char *cmd) {
   Command *rtn = malloc(sizeof(Command));
   
   rtn->numArgs = 1;
   rtn->args = NewArg(cmd);

   rtn->inFile[0] = rtn->outFile[0] = '\0';
   rtn->next = NULL;

   return rtn;
}

/* Delete "cmd" and all of its args */
static Command *DeleteCommand(Command *cmd) {
   Arg *temp;
   
   while (cmd->args != NULL) {
      temp = cmd->args;
      cmd->args = temp->next;
      free(temp);
   }
   return cmd->next;
}

/* Read from "in" a single cmdline, comprising one or more
 * pipe-connected commands. Return head pointer to the 
 * resulting line of commands */
static Command *ReadCommands(FILE *in) {
   int nextChar;
   char nextWord[MAX_WORD_LEN+1];
   Command *rtn, *lastCmd;
   Arg *lastArg;

   //If there is an executable, create a cmd for it, else rtn NULL
   if (1 == fscanf(in, WORD_FMT, nextWord)) {
      rtn = lastCmd = NewCommand(nextWord);
      lastArg = lastCmd->args;
   }
   else
      return NULL;

   //Repeatedly process the next blank delimited string
   do {
      while ((nextChar = getc(in)) == ' ') //skip whitespace
         ;

      //If the line is not over
      if (nextChar != '\n' && nextChar != EOF) {
         
         //A pipe indicates new command
         if (nextChar == '|') {
            if (1 == fscanf(in, WORD_FMT, nextWord)) {
               lastCmd = lastCmd->next = NewCommand(nextWord);
               lastArg = lastCmd->args;
            }
         }      
         //Otherwise, its a redirect or a cmdline arg
         else {
            ungetc(nextChar, in);
            fscanf(in, WORD_FMT, nextWord);
            if (!strcmp(nextWord, "<"))
               fscanf(in, WORD_FMT, lastCmd->inFile);
           else if (!strcmp(nextWord, ">"))
              fscanf(in, WORD_FMT, lastCmd->outFile);
           else {
              lastArg = lastArg->next = NewArg(nextWord);
              lastCmd->numArgs++;
           }
        }
     }
  } while (nextChar != '\n' && nextChar != EOF);

   return rtn;
}

static void RunCommands(Command *cmds) {
   Command *cmd;
   char **cmdArgs, **thisArg;
   Arg *arg;
   int childPID, cmdCount = 0;
   int pipeFDs[2]; //fds for pipe b/w this cmd and next
   int outFD = -1; //if not -1, fd of pipe/file use for stdout
   int inFD = -1;  //if not -1, fd of pipe/file to use for stdin
  
   for(cmd = cmds; cmd != NULL; cmd = cmd->next) {
      if (inFD < 0 && cmd->inFile[0]) //If no in-pipe, but input redirect
         inFD = open(cmd->inFile, O_RDONLY);
         
      if (cmd->next != NULL) //If there is a next cmd, make out-pipe
         pipe(pipeFDs);
   
      if ((childPID = fork()) < 0)
         fprintf(stderr, "Error, cannot fork.\n");
      else if (childPID) {   //Parent branch
         cmdCount++;
         close(inFD);        //Parent doesn't use inFD; child does
         if (cmd->next != NULL) {
            close(pipeFDs[1]); //Parent doesn't use out-pipe; child does
            inFD = pipeFDs[0]; //Next child's inFD will be out-pipe reader
         }
      }
      else {                //Child branch
         if (inFD >= 0) {   //IF special input (aka pipe or inFile), move to fd 0
            dup2(inFD, 0);
            close(inFD);
         }

         outFD = -1;        //Set up special stdout, if any
         if (cmd->next != NULL) { //If theres an out-pipe, use that
            outFD = pipeFDs[1];
            close(pipeFDs[0]);    //Next child reads out-pipe (set to inFD above)
         }
         if (outFD < 0 && cmd->outFile[0]) //if no out-pipe, but a redirect
              outFD = open(cmd->outFile, O_WRONLY|O_CREAT|O_TRUNC, 0644);

         //IF above code results in special stdout, dup this to fd 1 (otherwise, the "normal" stdout will be used)
         if (outFD >= 0) {
            dup2(outFD, 1);
            close(outFD);
         }

         //Build a command line args array, and point it to args content
         cmdArgs = thisArg = calloc(sizeof(char **), cmd->numArgs+1);
         for (arg = cmd->args; arg != NULL; arg = arg->next) 
            *thisArg++ = arg->value;
            
         //Exec the command, with given args, and with stdin/stdout
         //remapped if needed (aka remapped to pipe or in/out files)
         execvp(*cmdArgs, cmdArgs);
      }
   }

   //Wait on all children
   while (cmdCount--) 
      wait(NULL);
}           

int main() {
   Command *cmds;
   
   /* Repeatedly print a prompt, read cmdline, run it, and delete it */
   while (!feof(stdin)) {
      printf(">> ");
      if (NULL != (cmds = ReadCommands(stdin))) {
         RunCommands(cmds);
      }
      while (cmds != NULL) {
         cmds = DeleteCommand(cmds);
      }
   }
}

  














































