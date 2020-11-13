#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <limits.h>

#define MAX_DIGITS 20

void read(long long *results, char *filename) {
   FILE *file = fopen(filename, "r");
   int res, i = 0, j;
   long long sum = 0;
   while (EOF != res) { 
      fscanf(file, "%15llu", &results[i]);
      res = fscanf(file, "%*llu");
      printf("Read %llu\n", results[i]);
      i++;
   }
   i--;
   printf("max unsigned long long = %llu\n", ULLONG_MAX);
   for (j = 0; j < i; j++) {
      sum += results[j];
   }
   printf("sum = %llu\n", sum); 
}    

int main(int argc, char *argv[]) {
   long long results[100];
   if (argc < 2) {
      printf("Please provide input file.\n");
      exit(1);
   }
   read(results, argv[1]); 
   return 0;
}


