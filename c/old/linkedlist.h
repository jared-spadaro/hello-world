#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* data structure for each node in list.
 * this is a generic linked list so void 
 * pointer is used. 
 */
typedef struct node {
   void *data;
   struct node *next;
} Node;

/* initialize the linked list */
void init_list(Node **);

/* add new node to end of list */
void add_node(Node *, void *, size_t);

/* remove node with given data */
void remove_node(Node *, void *);

/* print all elements of list */
void print_list(Node *, void (*)(void *));

void print_int(void *);

void print_char(void *);

void list_driver();

#endif
