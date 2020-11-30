#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define ALL_PRIMES 5
#define ALL_SUITS 4
#define NO_ADJACENCIES 3
#define NO_REPEATS 2
#define NOTHING 1

/* You may find these includes useful, but they're not required */
   
   typedef struct card {
      char value;
      char suit;
   } card;

   card convertToCard (char *input) {
      card output;
      output.value = *input++;
      output.suit = *input;
   }

   int determineHand(char *inputString) {  //determine what hand the string earns
      return 0;
   }

   int compareHands (char *hand_one, char *hand_two) { //use to determine victorious hand
      return 0;
   }

   
   




   int main () {
      return 0;
   }
