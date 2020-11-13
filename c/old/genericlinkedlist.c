#include "linkedlist.h"

/* initialize the linked list */
void init_list(Node **head_p) {
   *head_p = malloc(sizeof(Node));
   (*head_p)->data = NULL;
   (*head_p)->next = NULL;
}

Node *new_node(size_t data_size) {
   Node *n = malloc(sizeof(Node));
   n->data = malloc(data_size);
   n->next = NULL;
   return n;
}

/* add new node to end of list */
void add_node(Node *head, void *data, size_t data_size) {
   Node *new = new_node(data_size), *temp;
   memcpy(new->data, data, data_size);
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
}

/* remove node with given data */
void remove_int(Node *head, void *data) {
   Node *temp = head, *to_remove;
   while (temp->next != NULL) {
      if (*(int *)(temp->next->data) == *(int *)data) {
         to_remove = temp->next;
         temp->next = temp->next->next;
         free(to_remove->data);
         free(to_remove);
      }
      temp = temp->next;
   }      
}

void remove_char(Node *head, void *data) {
   Node *temp = head, *to_remove;
   while (temp->next != NULL) {
      if (*(char *)(temp->next->data) == *(char *)data) {
         to_remove = temp->next;
         temp->next = temp->next->next;
         free(to_remove->data);
         free(to_remove);
      }
      temp = temp->next;
   }      
}

/* print all elements of list */
void print_list(Node *head, void (*fptr)(void *)) {
   Node *temp = head->next;
   int i = 0;
   while (temp != NULL) {
      printf("Element %d = ", i++);
      (*fptr)(temp->data);
      temp = temp->next; 
   }
   printf("\n");   
}

void print_int(void *x) {
   printf("%d\n", *(int *)x);
}

void print_char(void *c) {
   printf("%c\n", *(char *)c);
}

void list_driver() {
   Node *int_head, *char_head;
   int i;
   char c = 'A';

   init_list(&int_head);     
   for (i = 0; i < 10; i++) {
      add_node(int_head, &i, sizeof(int));
   }

   init_list(&char_head);
   for (i = 0; i < 10; i++) {
      add_node(char_head, &c, sizeof(char));
      c++;
   }

   print_list(int_head, print_int);
   print_list(char_head, print_char);

   i = 5, c = 'C';
   remove_int(int_head, &i);
   remove_char(char_head, &c);

   print_list(int_head, print_int);
   print_list(char_head, print_char);
}  

int main (void) {
   list_driver();
   return 0;
}






