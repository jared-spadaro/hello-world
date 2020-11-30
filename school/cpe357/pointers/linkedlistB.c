Node *AddSecond(Node *head, int val) {
   Node *newNode = malloc(sizeof(Node));
   newNode->data = val;
   newNode->next = NULL;
   if (head == NULL) {
      head = newNode;
   }
   else {
      newNode->next = head->next;
      head->next = newNode;
   }
   return head;
}
