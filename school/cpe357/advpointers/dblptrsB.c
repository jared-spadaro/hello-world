#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
   int data;
   struct Node *next;
} Node;

void ReadList(Node **pHead) {
   int data;
   Node *nd, *temp; // You may use temp, but don't have to.
   *pHead = NULL;
   scanf("%d", &data);        
   while (data) { 
      nd = malloc(sizeof(Node));
      nd->data = data;
      nd->next = NULL;                 
      if (!*pHead) {
         *pHead = nd;
         temp = *pHead;
      }
      else {
         temp->next = nd;
         temp = temp->next;     
      } 
      scanf("%d", &data);     
   }                          
}

void PrintList(Node *head) {
   while (head) {
      printf("%d ", head->data);
      head = head->next;
   }
   printf("\n");
}

void ConcatLists(Node **head1, Node **head2) {
   Node *temp; // You may use this, but you don't have to.
   temp = *head1;               
   if (temp) {
      while (temp->next != NULL) { 
         temp = temp->next;
      }                            
      temp->next = *head2;
   }
   else {
      *head1 = *head2;
   }
   *head2 = NULL;
}

int main() {
Node *head1, *head2;

printf("Reading Lists...\n");
ReadList(&head1);
ReadList(&head2);
printf("Concatenating Lists...\n");
ConcatLists(&head1, &head2);
printf("Printing Lists...\n");
PrintList(head1);
PrintList(head2);

return 0;
}
