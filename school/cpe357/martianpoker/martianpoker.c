#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//for primes
#define ACE 'A'
#define TWO '2'
#define THREE '3'
#define FOUR '4'
#define FIVE '5'
#define SIX '6'
#define SEVEN '7'
#define EIGHT '8'
#define NINE '9'
#define TEN 'T'
#define JACK 'J'
#define QUEEN 'Q'
#define KING 'K'

//for suits
#define SPADE 'S'
#define CLUB 'C'
#define HEART 'H'
#define DIAMOND 'D'

#define SPADES 3
#define HEARTS 2
#define DIAMONDS 1
#define CLUBS 0

#define ACE_RANK 49
#define TEN_RANK 58
#define JACK_RANK 59
#define QUEEN_RANK 60
#define KING_RANK 61

#define HAND_SIZE 10
#define NUM_CARDS 5

#define ALL_PRIMES 4
#define ALL_SUITS 3
#define NO_ADJACENCIES 2
#define NO_REPEATS 1
#define NOTHING 0

#define LINE_SIZE 4096
/* You may find these includes useful, but they're not required */

int isAllPrime (char hand[]);
int repeatedSuit (char hand[]);
int isAllSuits (char hand[]);
char convertLetter (char c);
int isNoAdjacencies (char hand[]);
int isNoRepeats (char hand[]);
void sortHand (char hand[], int length);
void sortLine (char line[], int length);
int rankCompare (char leftHand[], char rightHand[]);
void readAndCheckLines (char line[], int length, char leftHand[], char rightHand[]);
int isLineValid(char line[], int length);
char *handTranslator (int handRank);
int winningHand (char leftHand[], char rightHand[]);
int findBestHand (char hand[]);

typedef struct {
   char rank;
   char suit;
} Card;

//lines are validated by the time they reach this point   
//return 0 if neither is, -1 if left hand is, 1 if right hand is, 2 if both are
int isAllPrime (char hand[]) {
   char rank;
   int i = 0, isAllPrime = 0, numPrimes = 0;
   while(i < HAND_SIZE) {
      rank = hand[i]; 
      if(rank == TWO || rank == THREE || rank == FIVE || rank == SEVEN ||
         rank == JACK || rank == KING) { //then card is prime
         numPrimes++;
      }
      i += 2; //parse past the rank and the following suit. we want the next rank
   }
   if(numPrimes == NUM_CARDS) isAllPrime = 1;
   return isAllPrime;
}

//-1 for left win, 1 for right win, 0 for tie
int repeatedSuit (char hand[]) {
   int i = 0;
   char spades = 0, clubs = 0, hearts = 0, diamonds = 0, suit;
   while(i < HAND_SIZE) {
      i++; //parse past rank. we only care about the suit
      suit = hand[i];
      if(suit == SPADE) {
         spades++;
      }
      else if(suit == CLUB) {
         clubs++;
      }
      else if(suit == HEART) {
         hearts++;
      }
      else {
         diamonds++;
      }
      i++; //go to next rank (which we will parse past at start of loop to reach next suit)
   }
   if(spades > 1) {
       suit = SPADES;
   }
   else if(hearts > 1) {
      suit = HEARTS;
   }
   else if(diamonds > 1) {
      suit = DIAMONDS;
   }
   else {
      suit = CLUBS;
   }
   return suit;
}


int isAllSuits (char hand[]) {
   char suit; 
   int i = 0, isAllSuits = 0, hearts = 0, diamonds = 0, spades = 0, clubs = 0;
   while(i < HAND_SIZE) {
      i++; //parse past rank. we only care about the suit
      suit = hand[i];
      if(suit == SPADE) {
         spades = 1;
      }
      else if(suit == CLUB) {
         clubs = 1;
      }
      else if(suit == HEART) {
         hearts = 1;
      }
      else {
         diamonds = 1;
      }
      i++; //go to next rank (which we will parse past at start of loop to reach next suit)
   }
   if(spades && clubs && hearts && diamonds) {
      isAllSuits = 1;
   }
   return isAllSuits;
}

char convertLetter (char c) {
   if(isalpha(c)) {
      if(c == 'A') c = ACE_RANK;
      else if(c == 'T') c = TEN_RANK;
      else if(c == 'J') c = JACK_RANK;
      else if(c == 'Q') c = QUEEN_RANK;
      else c = KING_RANK;
   }
   return c;
}


int isNoAdjacencies (char hand[]) {
   char curr = 0, next = 0;
   int i = 0, j = 0, isNoAdj = 1;
   while(i < HAND_SIZE-2) {
      curr = convertLetter(hand[i]);
      next = convertLetter(hand[i+2]);
      if(curr == next || curr == next + 1 || curr == next - 1) {
         isNoAdj = 0; //we've found an adjacency, so set to 0
      }   
      i+=2;
   }
   if(!isNoRepeats(hand)) isNoAdj = 0; //if there are repeats, this hand is not valid
   return isNoAdj;
}


int isNoRepeats (char hand[]) {
   int isNoRepeats = 1, i = 0, j = 0;
   while(i < HAND_SIZE) {
      for(j=i+2;j<HAND_SIZE-1;j+=2) {
         if(hand[i] == hand[j]) {
            isNoRepeats = 0;          
         }
      }
      i+=2;
   }
   return isNoRepeats;
}

void sortHand (char hand[], int length) {
   Card cards[NUM_CARDS];
   Card curr;
   int i = 0, j = 0;
   while(i < HAND_SIZE) {
      cards[j].rank = hand[i];
      cards[j].suit = hand[i+1];
      j++;
      i+=2;
   }
 
   for(i=1;i<NUM_CARDS;i++) {
      curr = cards[i];
      j = i;
      while(j > 0 && convertLetter(curr.rank) < convertLetter(cards[j-1].rank)) {
         cards[j] = cards[j-1];
         j--;
      }
      cards[j] = curr;
   }

   i = 0;
   j = 0;
   while(i < HAND_SIZE) {
      hand[i] = cards[j].rank;
      hand[i+1] = cards[j].suit; 
      i+=2;
      j++;
   }  
}          

void sortLine (char line[], int length) {
   int curr, i = 0, j = 0;
   for(i=1;i<length;i++) {
      curr = line[i];
      j = i;
      while(j > 0 && curr >= line[j-1]) {
         line[j] = line[j-1];
         j--;
      }
      line[j] = curr;
   }
}

int rankCompare (char leftHand[], char rightHand[]) {
   int status = 0,  i = 0, j = 0;
   char numericLeft[NUM_CARDS], numericRight[NUM_CARDS];
   while(i < HAND_SIZE) { 
      numericLeft[j] = convertLetter(leftHand[i]);
      numericRight[j] = convertLetter(rightHand[i]);
      j++;
      i+=2;  //go to next rank
   }

   sortLine(numericLeft, NUM_CARDS); 
   sortLine(numericRight, NUM_CARDS);

   i = 0;
   while(i<NUM_CARDS) {
      if(numericLeft[i] > numericRight[i]) {
         status = -1;
         i = NUM_CARDS+1;
      }
      else if(numericLeft[i] < numericRight[i]) {
         status = 1;
         i = NUM_CARDS+1;
      }
      else { //first numbers are equal so check the next
         i++;
      }
   }
   return status;
}   


      
void readAndCheckLines (char line[], int length, char leftHand[], char rightHand[]) {
   int i = 0, j = 0, k = 0, result = 0;
   while(fgets(line, length, stdin) != NULL) {
      if(isLineValid(line, length) == 1) {
         for(i=0; i<strlen(line); i++) {
            if(line[i] != ' ' && line[i] != '\t') {
               if(j < HAND_SIZE) {
                  leftHand[j] = toupper(line[i]);
                  j++;
               }
               else {
                  rightHand[k] = toupper(line[i]);
                  k++;
               }
            }
         }
         j = 0;
         k = 0;    

         result = winningHand(leftHand,rightHand);
         if(result == 0) {  //break tie with either rankCompare or suitTieBreak
            result = rankCompare(leftHand, rightHand);
            if(result == 0 && findBestHand(leftHand) == ALL_SUITS) {  //use suitTieBreak
               if(repeatedSuit(leftHand) > repeatedSuit(rightHand)) {
                  result = -1;
               }
               else if(repeatedSuit(rightHand) > repeatedSuit(leftHand)) {
                  result = 1;
               }
               else {
                  result = 0;
               }
            }   
         }
         i = 0;

         sortHand(leftHand, HAND_SIZE);
         sortHand(rightHand, HAND_SIZE);

         //at this point, all ties are resolved and we are ready to print 
         while(i < HAND_SIZE-1) {
            if(result == -1 || result == 0) {    //if left wins or its a tie, print left first
               printf("%c%c ", leftHand[i], leftHand[i+1]);
            }  
            else {  //result must be 1; print right first
               printf("%c%c ", rightHand[i], rightHand[i+1]);
            }
            i+=2;
         }
         i = 0;
         if(result == -1) {
            printf("%s beats ", handTranslator(findBestHand(leftHand)));
         }
         else if(result == 1) {
            printf("%s beats ", handTranslator(findBestHand(rightHand)));
         }
         else { //result is 0
            printf("%s ties ", handTranslator(findBestHand(leftHand)));
         }
               
         while(i < HAND_SIZE-1) {
            if(result == -1 || result == 0) {    //if left wins or its a tie, print right second
               printf("%c%c ", rightHand[i], rightHand[i+1]);
            }  
            else {  //result must be 1; print left second
               printf("%c%c ", leftHand[i], leftHand[i+1]);
            }
            i+=2;
         }
         i = 0;
         if(result == -1) {
            printf("%s \n", handTranslator(findBestHand(rightHand)));
         }
         else if(result == 1) {
            printf("%s \n", handTranslator(findBestHand(leftHand)));
         }
         else { //result is 0
            printf("%s \n", handTranslator(findBestHand(rightHand)));
         }
               

                     
      }
      else if(isLineValid(line, length) == -1) {
         printf("Bad Hands\n");
      }
      else {
    
      }
   }
}

char *handTranslator (int hand) {
   char *handName;
   if(hand == ALL_PRIMES) {
      handName = "All Primes";
   }
   else if(hand == ALL_SUITS) {
      handName = "All Suits";
   }
   else if(hand == NO_ADJACENCIES) {
      handName = "No Adjacencies";
   }
   else if(hand == NO_REPEATS) {
      handName = "No Repeats";
   }
   else {
      handName = "Nothing";  
   }
   return handName;
}    


//pass this fuction BEST hand of each
//-1 for left win, 1 for right win, 0 for tie
int winningHand (char leftHand[], char rightHand[]) {
   int result = 0; 
   int left = findBestHand(leftHand); 
   int right = findBestHand(rightHand);
   if(left > right) {  //left has a better hand
      result = -1;
   }
   else if(left < right) { //right has a better hand   
      result = 1;
   }
   else {   //the two hands are equal; break tie with either rankCompare and/or suitTieBreak
      result = 0;
   }
   return result;
}


int findBestHand (char hand[]) {
   int bestHand;
   if(isAllPrime(hand)) {
      bestHand = ALL_PRIMES;
   }
   else if(isAllSuits(hand)) {
      bestHand = ALL_SUITS;
   }
   else if(isNoAdjacencies(hand)) {
      bestHand = NO_ADJACENCIES;
   }
   else if(isNoRepeats(hand)) {
      bestHand = NO_REPEATS;
   }
   else {
      bestHand = NOTHING;
   }
   return bestHand;
}   
        
int isRank (char rank) {
   char isRank;
   if(rank == ACE || rank == TWO || rank == THREE || rank == FOUR) {
      isRank = 1;
   }
   else if( rank == FIVE || rank == SIX ||  rank == SEVEN || rank == EIGHT) {
      isRank = 1;
   }
   else if(rank == NINE || rank == TEN || rank == JACK || rank == QUEEN || rank == KING) {
      isRank = 1;
   }
   else {
      isRank = 0;
   }
   return isRank;
}



int isLineValid (char line[], int length) {
   int isBlank = 1, rank, suit, numCards = 0, i = 0, isValid = -1, flag = 1, white = 0;
   while(line[i] != '\n' && flag) {  //run until we hit end of line or we determine that line is invalid
      while(line[i] == ' ' || line[i] == '\t') i++; //eliminate leading whitespace
      rank = line[i];
      rank = toupper(rank);
      
      if(isRank(rank)) {
         //if rank is valid, proceed to next char
         i++;
         //now we are at suit
         suit = line[i];
         suit = toupper(suit);
         if(suit == SPADE || suit == HEART || suit == CLUB || suit == DIAMOND) { //if suit is valid (this inherently checks for whitespace!)
            numCards++;
            i++;
            while(line[i] == ' ' || line[i] == '\t') {
               white++;
               i++;
            }  
         }
         else {
            flag = 0;
         }
      }
      else {
         flag = 0;
      }
      if (!white && numCards != 10) {
         flag = 0;
      }
      white = 0;
   }
   i = 0;
   //now make sure that there are 10 cards and that flag was never cleared
   if(numCards == HAND_SIZE && flag) isValid = 1;

   while (line[i] != '\n') {
      if(!isspace(line[i])) {
         isBlank = 0;
      }
      i++;
   }
   if(isBlank) { //if we encountered a non-space character after last card
      isValid = 0;
   }
   return isValid;
}   



int main () {
   char line[LINE_SIZE], leftHand[HAND_SIZE*2], rightHand[HAND_SIZE*2];
   int length = LINE_SIZE;
   readAndCheckLines(line, length, leftHand, rightHand);
   isAllPrime(line);
   return 0;
} 
