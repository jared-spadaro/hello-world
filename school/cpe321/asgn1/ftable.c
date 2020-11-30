/* cpe321 program 1 - ftable
 * by Jared Spadaro
 * with Professor Nico
 * description: ftable counts the frequency of letters
 * appearing in a message provided by the user
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define NUM_LETTERS 26

void usage() {
   printf("usage: ftable [-v] [-s num] [-p num] [infile [outfile]]\n");
   exit(1);
}

/* checking return value of fopen */
FILE *safe_fopen(char *file, char *perm) {
   FILE *ret;
 
   ret = fopen(file, perm);
   if (ret == NULL) {
      perror("fopen");
      exit(1);
   }
   return ret;
}

/* set variables according to flags */
void check_flag(char flag, int *ndx, char **argv, 
 int *is_verbose, int *start, int *period) {
   if (flag == 'v') {
      *is_verbose = 1;
   }
   else if (flag == 's') {
      *start = atoi(argv[*ndx+1]);
      (*ndx)++;
   }
   else if (flag == 'p') {
      *period = atoi(argv[*ndx+1]);
      (*ndx)++;
   }
   else {
      usage();
   }
}

/* usage: ftable [-v] [-s num] [-p num] [infile [outfile]] */
void process_args(int argc, char **argv, FILE **in, 
 FILE **out, int *is_verbose, int *start, int *period) {
   int i, flag = 0;

   if (argc > 8) {
      usage();
   }

   for (i = 1; i < argc; i++) {
      if (argv[i][0] == '-') {
         check_flag(argv[i][1], &i, argv, is_verbose, start, period);
      }
      else {
         if (!flag) {
            *in = safe_fopen(argv[i], "r");
            flag = 1;
         }
         else {
            *out = safe_fopen(argv[i], "w");
         }
      }
   } 
}        

/* do some basic analysis and print out the results */
void analysis(int *freq_table, int total) {
   int i,j;
   float percent;

   printf("total chars: %d\n", total);
   
   for (i = 0; i < NUM_LETTERS; i++) {
      if (total) {
         percent = ((float)freq_table[i] / (float)total) * 100;
      }
      else {
         percent = 0;
      }
      printf("%c: %9d (%5.2f%%) ", i + 65, freq_table[i], percent);
      for (j = 0; j < ceil(percent); j++) {
         printf("*");
      }
      printf("\n");
   }
} 

/* count the appearance of letters, histogram-style */
void ftable(int *is_verbose, int *start, int *period, FILE *in, FILE *out) {
   int i = 0, total = 0;
   char temp;
   int *freq_table = calloc(sizeof(int), NUM_LETTERS);

   while (i <= *start) {
      temp = toupper(fgetc(in));
      if (isalpha(temp)) {
         i++;
      }
      if (temp == EOF) {
         i = *start + 1;
      }
   }

   while (temp != EOF) {
      i = 0;
      if (isalpha(temp)) {
         freq_table[temp - 65]++;
         total++;
      }
      while (i < *period) {
         temp = toupper(fgetc(in));
         if (isalpha(temp)) {
            i++;
         }
         if (temp == EOF) {
            i = *period;
         }
      }
   }
   analysis(freq_table, total);
} 

int main (int argc, char **argv) {
   FILE **in, **out;
   int *is_verbose, *start, *period;

   in = malloc(sizeof(FILE *));
   out = malloc(sizeof(FILE *));
   is_verbose = malloc(sizeof(int));
   start = malloc(sizeof(int));
   period = malloc(sizeof(int));

   *in = stdin;
   *out = stdout;
   *is_verbose = 0;
   *start = 0;
   *period = 1;

   process_args(argc, argv, in, out, is_verbose, start, period);

   ftable(is_verbose, start, period, *in, *out);

   return 0;
}
