#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* data structure for each node in list.
 * this is a generic linked list so void 
 * pointer is used. 
 */
typedef struct node {
   int data;
   struct node *next;
} Node;

Node *new_node(int data) {
   Node *new = malloc(sizeof(Node));
   new->data = data;
   new->next = NULL;
   return new;
}

/* add new node to end of list */
Node *add_node(Node *head, int data) {
   Node *temp, *new = new_node(data);
   if (!head) {
      head = new_node((int)NULL);
   }
   if (!head->next) {
      head->next = new;
   }
   else {
      temp = head;
      while (temp->next != NULL) {
         temp = temp->next;
      }
      temp->next = new;
   }
   return head;  
}

/* remove node with given data */
void remove_node(Node *head, int data) {
   Node *temp = head, *to_remove;
   while (temp->next != NULL) {
      if (temp->next->data == data) {
         to_remove = temp->next;
         temp->next = temp->next->next;
         free(to_remove);
      }
      else {
         temp = temp->next;
      }
   }      
}

/* print all elements of list */
void print_list(Node *head) {
   Node *temp = head->next;
   int i = 0;
   while (temp != NULL) {
      printf("Element %d = %d\n", i++, temp->data);
      temp = temp->next; 
   }
   printf("\n");   
}

/* add value in order to an already sorted linked list */
void insert_in_order(Node *head, int data) {
   Node *temp = head, *new, *temp2;
   int check = 0;
   if (!head) {
      head = add_node(head, data);
   }
   else {
      new = new_node(data);
      while (temp->next != NULL && !check) {
         if (temp->next->data >= data) {
            temp2 = temp->next;
            temp->next = new;
            new->next = temp2;
            check = 1;  
         }
         else {
            temp = temp->next;
         }
      }
      if (!check) {
         head = add_node(head, data);
      }
   }
}           

void list_driver() {
   Node *head;
   int i;
     
   for (i = 0; i < 10; i++) {
      head = add_node(head, i);
   }

   print_list(head);

   i = 5;
   remove_node(head, i);
   insert_in_order(head, 11);
   insert_in_order(head, 4);
   insert_in_order(head, 2);
   insert_in_order(head, -1);
   insert_in_order(head, 7);
   insert_in_order(head, 14);
   insert_in_order(head, 0);
   remove_node(head, 2);
   remove_node(head, 14);
   print_list(head);
}  
              
int main (void) {
   list_driver();
   return 0;
}






