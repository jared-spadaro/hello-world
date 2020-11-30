/* cpe321 program 1 - vig
 * by Jared Spadaro
 * with Professor Nico
 * description: vig enciphers or deciphers a 
 * given message using the vigenere cipher
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

/* check return value of fopen */
FILE *safe_fopen(char *file, char *perm) {
   FILE *ret;

   ret = fopen(file, perm);
   if (ret == NULL) {
      perror("fopen");
      exit(1);
   }
   return ret;
}

void usage() {
   printf("usage: ./vig [-d] key [infile [outfile]]\n");
   exit(1);
}

/* check key for validity (alpha chars only) */
void check_key(char *key) {
   int i = 0, len = strlen(key);

   while (i < len) {
      if (!isalpha(key[i])) {
         usage();
      }
      i++;
   }
}

/* check user-inputted arguments */
void process_args(int argc, char **argv, FILE **in, 
 FILE **out, int *decipher, char **key) {
   
   *decipher = 0;
   if (argc < 2 || argc > 5) {
      usage();
   }
   /* check for any optional args */
   if (argc > 2) {
      if (argv[1][0] == '-') {
         if (argv[1][1] != 'd') {
            usage();
         }
         else {
            *decipher = 1;
         }
         
         /* check key for numbers */
         check_key(argv[2]);
         *key = argv[2];

         /* check for in/out files */
         if (argc > 3) {
            *in = safe_fopen(argv[3], "r");
            if (argc > 4) {
               *out = safe_fopen(argv[4], "w");
            }
         }
      }
      else {
         /* enciphering */
         check_key(argv[1]);
         *key = argv[1];

         *in = safe_fopen(argv[2], "r");
         if (argc > 3) {
            *out = safe_fopen(argv[3], "w");
         }
      }
   }
   /* no optional args included */
   else {
      check_key(argv[1]);
      *key = argv[1];
   }
}

/* take message and encipher it using vigenere cipher */
void encipher(char *key, FILE *in, FILE *out) {
   char msg_temp, key_temp, enciphered;
   int i = 0, key_len = strlen(key);

   msg_temp = toupper(fgetc(in));
   while (msg_temp != EOF) {
      if (isalpha(msg_temp)) {
         key_temp = toupper(key[i]);
 
         /* this is where the magic happens. reduce 
          *  by 65 so we can mod 26 for rollover */
         enciphered = (((key_temp - 65) + (msg_temp - 65)) % 26) + 65; 

         fprintf(out, "%c", enciphered);
         i++;
      }
      else {
         /* not a letter so just print it and move on */
         fprintf(out, "%c", msg_temp);
      }
      msg_temp = toupper(fgetc(in));

      if (i == key_len) {
         i = 0;
      }
   }
}

/* take enciphered message and decipher it */
void decipher(char *key, FILE *in, FILE *out) {
   char msg_temp, key_temp, deciphered;
   int i = 0, key_len = strlen(key);

   msg_temp = toupper(fgetc(in));
   while (msg_temp != EOF) {
      if (isalpha(msg_temp)) {
         key_temp = toupper(key[i]);

         /* offset by (26 - key) */ 
         deciphered = (((msg_temp - 65) + (26 - (key_temp - 65))) % 26) + 65; 

         fprintf(out, "%c", deciphered);
         i++;
      }
      else {
         fprintf(out, "%c", msg_temp);
      }
      msg_temp = toupper(fgetc(in));

      if (i == key_len) {
         i = 0;
      }
   }
}

int main (int argc, char **argv) {
   FILE **in, **out; 
   int *is_decipher;
   char **key;
   
   in = malloc(sizeof(FILE *));
   out = malloc(sizeof(FILE *));
   is_decipher = malloc(sizeof(int));
   key = malloc(sizeof(char *));

   *in = stdin;
   *out = stdout;

   process_args(argc, argv, in, out, is_decipher, key);

   if (*is_decipher) {
      decipher(*key, *in, *out);
   }
   else {
      encipher(*key, *in, *out);
   }

   return 0;
}
