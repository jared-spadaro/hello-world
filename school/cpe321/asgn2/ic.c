#include <stdlib.h>
#include <stdio.h>

void usage() {
   printf("usage: ic N l [ 12 [...] ]\n");
   exit(1);
}

void process_args(int argc, char **argv, int *msg_len, int *key_lens) {
   int i, j = 0;

   if (argc < 3) {
      usage();
   }

   *msg_len = atoi(argv[1]);

   for (i = 2; i < argc; i++) {
      key_lens[j] = atoi(argv[i]);   
      j++;
   }
}

void ic(int msg_len, int *key_lens, int num_keys) {
   int i;
   float arg_one, arg_two;

   printf("Key  Expected IC (N=%d)\n", msg_len);
   printf("---- ------------------\n");

   for (i = 0; i < num_keys; i++) {
      arg_one = 0;
      arg_two = 0;

      arg_one = 1 / (float)key_lens[i];
      arg_one *= (float)(msg_len - key_lens[i]) / (float)(msg_len - 1);
      arg_one *= 0.066;

      arg_two = (float)(key_lens[i] - 1) / (float)key_lens[i];
      arg_two *= (float)msg_len / (float)(msg_len - 1);
      arg_two *= 0.038;

      printf("%4d %1.4f\n", key_lens[i], arg_one + arg_two);
   }
}

int main (int argc, char **argv) {
   int num_keys, *msg_len, *key_lens;
   
   num_keys = argc - 2;
   msg_len = malloc(sizeof(int));
   key_lens = malloc(sizeof(int) * num_keys);
 
   process_args(argc, argv, msg_len, key_lens);
   ic(*msg_len, key_lens, num_keys);

   return 0;
}
