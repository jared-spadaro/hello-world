#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_LEN 64
#define MAX_SUBSTRINGS 16384
#define MAX_TOTAL 65536

typedef struct substring_t {
   int count;
   int location;
   int length;
   int used;
   int dist[MAX_LEN];
   char str[MAX_LEN];
} substring_t;

void usage() {
   printf("usage: kasiski [-v] [-d] [-m length] [infile [outfile]]\n");
   exit(1);
}

FILE *safe_fopen(char *file, char *perm) {
   FILE *ret;
 
   ret = fopen(file, perm);
   if (ret == NULL) {
      perror("fopen");
      exit(1);
   }
   return ret;
}

void check_flag(char flag, int *ndx, char **argv, 
 int *is_verbose, int *min, int *dist) {
   if (flag == 'v') {
      *is_verbose = 1;
   }
   else if (flag == 'd') {
      *dist = 1;
   }
   else if (flag == 'm') {
      *min = atoi(argv[*ndx+1]);
      (*ndx)++;
   }
   else {
      usage();
   }
}

/* usage: kasiski [-v] [-d] [-m length] [infile [outfile]] */
void process_args(int argc, char **argv, FILE **in, 
 FILE **out, int *is_verbose, int *min, int *dist) {
   int i, flag = 0;

   if (argc > 7) {
      usage();
   }

   for (i = 1; i < argc; i++) {
      if (argv[i][0] == '-') {
         check_flag(argv[i][1], &i, argv, is_verbose, min, dist);
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

int find_matches(int min, int dist, substring_t *str_list, 
 int num_str, substring_t *master_list, int *master_total) {
   int i, j, num_matches = 0;
   substring_t *temp, *temp_two;

   for (i = 0; i < num_str; i++) {
      temp = str_list + i;
      /* only search for matches if it hasn't been matched already */
      if (!temp->used) {
         for (j = i + 1; j < num_str; j++) {
            temp_two = str_list + j;
            if (!strncmp(temp_two->str, temp->str, min) && !temp_two->used) {
               temp->dist[temp->count - 1] = 
                temp_two->location - temp->location;
               temp->count++;
               temp_two->used = 1;               
            }
         }
      }
   }

   for (i = 0; i < num_str; i++) {
      temp = str_list + i;
      if (temp->count > 1) {
          temp->used = 0;
          temp->str[temp->length] = '\0';
          num_matches++;
          memcpy(master_list + *master_total, temp, sizeof(substring_t));
          (*master_total)++;
      }
   } 
   return num_matches;
}

/* searches for matching substrings. returns number of matches found */
int kasiski(int is_verbose, int len, int dist, FILE *in, FILE *out,
 substring_t *master_list, int *master_total) {
   int total = 0, str_ndx = 0, list_ndx = 0, i = 0;
   char temp = 0;
   substring_t *temp_list;
   substring_t *str_list = calloc(sizeof(substring_t), MAX_SUBSTRINGS);

   fseek(in, 0, SEEK_SET);

   temp = toupper(fgetc(in));

   /* parse into [min]-letter substrings */
   while (temp != EOF) {
      if (isalpha(temp)) {
         (str_list + list_ndx)->str[str_ndx] = temp;
         str_ndx++;
         total++;

         if (str_ndx == len) {
            memcpy((char *)((str_list + list_ndx + 1)->str), 
             (char *)(((str_list + list_ndx)->str) + 1), len - 1);
            (str_list + list_ndx)->count = 1;
            list_ndx++;
            str_ndx = len - 1;  
         }
      }
      temp = toupper(fgetc(in));
   }

   for (i = 0; i < list_ndx; i++) {
      temp_list = str_list + i;
      temp_list->location = i;
      temp_list->length = len;
   }

   return find_matches(len, dist, str_list, 
    list_ndx, master_list, master_total);

} 

int compare(const void *a, const void *b) {
   substring_t *temp_one = (substring_t *)a;
   substring_t *temp_two = (substring_t *)b;
   int ret  = 0;

   if (temp_one->length > temp_two->length) {
      ret = -1;
   }
   else if (temp_one->length < temp_two->length) {
      ret = 1;
   }
   else {
      if (temp_one->count > temp_two->count) {
         ret = -1;
      }
      else if (temp_one->count < temp_two->count) {
         ret = 1;
      }
      else {
         if (strcmp(temp_one->str, temp_two->str) > 0) {
            ret = 1;
         }
         else if (strcmp(temp_one->str, temp_two->str) < 0) {
            ret = -1;
         }
         else {
            ret = 0;
         }
      }
   }
   return ret;
}

void print_string(substring_t *temp, int *dist, int max_len) {
   int j;  

   printf("%6d", temp->length);
   printf("  %6d  ", temp->count);
   printf("%*s  ", max_len, temp->str);
   if (*dist) {
      for (j = 0; j < temp->count - 1; j++) {
         if (temp->dist[j] >= temp->length) {
            printf("%d ", temp->dist[j]);
         }
      }
      printf("\n");
   }
   else {
      printf("  %d ", temp->location);
      for (j = 0; j < temp->count - 1; j++) {
         printf("%d ", temp->dist[j] + temp->location);
      }
      printf("\n");
   }
}

void print_results(substring_t *master_list, int *master_total, int *dist) {
   int i;   
   substring_t *temp;
   const char *word = "Word";
   const char *space = "====";

   qsort(master_list, *master_total, sizeof(substring_t), compare);

   printf("Length  Count  %s   ", word);              
   if (*dist) {
      printf("Distances\n");
   }
   else {
      printf("Locations\n");
   }
   printf("======  =====  %s   =========\n", space);

   for (i = 0; i < *master_total; i++) {
      temp = master_list + i;
      print_string(temp, dist, master_list->length);
   }
}

int main (int argc, char **argv) {
   FILE **in, **out;
   int i = 0, ret = 1, *is_verbose, *min, *dist, *master_total;
   substring_t *master_list;

   in = malloc(sizeof(FILE *));
   out = malloc(sizeof(FILE *));
   is_verbose = calloc(sizeof(int), 1);
   min = malloc(sizeof(int));
   dist = calloc(sizeof(int), 1);
   master_total = calloc(sizeof(int), 1);
   master_list = calloc(sizeof(substring_t), MAX_TOTAL);

   *in = stdin;
   *out = stdout;
   *is_verbose = 0;
   *min = 3;

   process_args(argc, argv, in, out, is_verbose, min, dist);

   while (ret) {
      ret = kasiski(*is_verbose, (*min) + i, *dist, *in, *out, master_list, 
       master_total);
      i++;
   }

   print_results(master_list, master_total, dist);

   return 0;
}

