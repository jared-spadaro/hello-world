#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
   int data;
   struct node *left;
   struct node *right;
} NODE;

NODE *new_node(int data) {
   NODE *node = malloc(sizeof(NODE));
   node->data = data;
   node->left = NULL;
   node->right = NULL;
   return node;
}

/* add new node in order to bst */
void add_node(NODE *root, int data) {
   NODE *temp;
   int flag = 0;
   if (root == NULL) {
      root = new_node(data);
   }
   else {
      temp = root;
      while (!flag) {
         if (data < temp->data) {
            if (temp->left) temp = temp->left;
            else {
               temp->left = new_node(data);
               flag = 1;
            }
         }
         else {
            if (temp->right) temp = temp->right;
            else {
               temp->right = new_node(data);
               flag = 1;
            }
         }
      }
   }
}

NODE *delete_node(NODE *root, int data) {
   if (!root) return NULL;

   NODE *temp;
   /* first find the node you want to delete */
   if (data < root->data) {
      root->left = delete_node(root->left, data);
   }
   else if (data > root->data) {
      root->right = delete_node(root->right, data);
   }
   /* in this case, we have found node we want to delete */
   else {
      if (!root->left) {
         temp = root->right;
         free(root);
         root = temp;
      }
      else if (!root->right) {
         temp = root->left;
         free(root);
         root = temp;
      } 
      else {
         temp = root->right;
         NODE *prev = NULL;
         while (temp->left) {
            prev = temp;
            temp = temp->left;
         }
         root->data = temp->data;
         if (prev) {
            prev->left = delete_node(prev->left, prev->left->data);
         }
         else {
            root->right = delete_node(root->right, root->right->data);
         }
      }
   }
   return root;
}
 
NODE *search (NODE *root, int key) {
   if (!root) return NULL;

   NODE *temp = root;
   while (temp) {
      if (key == temp->data) {
         return temp;
      }
      else if (key < temp->data) {
         temp = temp->left;
      }
      else {
         temp = temp->right;
      }
    }
   return NULL;
}
  
void print_bst (NODE *root) {
   if (root == NULL) return;
   printf("%d", root->data);
   if (root->left) printf("(L:%d)", root->left->data);
   if (root->right) printf("(R:%d)", root->right->data);
   printf("\n");
   print_bst(root->left);
   print_bst(root->right);
}

void bst_driver() {
   int i;
   srand(time(NULL));
   NODE *root = new_node(rand() % 100);
   for (i = 0; i < 10; i++) {
      add_node(root, rand() % 100);
   }
   print_bst(root);
   delete_node(root, root->right->left->data);
   print_bst(root);
}
        
int main(void) {
   bst_driver();
   return 0;    
}
