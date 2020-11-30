#include <stdio.h>
#include <strings.h>

#define MAX 100

typedef struct {
   int val1;
   int val2;
} Pair;

int Compare (Pair *p1, Pair *p2) {
   if(p1->val1 > p2->val1) return 1;
   else if(p1->val1 < p2->val1) return 0;
   return (p1->val2 >= p2->val2);
}

void Swap (Pair *p1, Pair *p2) {
   int temp1 = p1->val1, temp2 = p1->val2;
   p1->val1 = p2->val1;
   p1->val2 = p2->val2;
   p2->val1 = temp1;
   p2->val2 = temp2;
}

int main (void) {

   Pair p1 = {6,4}, p2 = {5,2};
   Pair *ptr1 = &p1, *ptr2 = &p2;
   printf("Pair 1 = {%d, %d}\n", ptr1->val1,ptr1->val2);  
   printf("Pair 2 = {%d, %d}\n", ptr2->val1,ptr2->val2);
   printf("Compare: %d\n", Compare(ptr1,ptr2));
   Swap(ptr1,ptr2);
   printf("After swap...\n");
   printf("Pair 1 = {%d, %d}\n", ptr1->val1,ptr1->val2);  
   printf("Pair 2 = {%d, %d}\n", ptr2->val1,ptr2->val2);
   printf("Compare: %d\n", Compare(ptr1,ptr2));

      
   return 0;

}
