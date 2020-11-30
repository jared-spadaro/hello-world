#ifndef PROBLEM3_H
#define PROBLEM3_H

#include <stdlib.h>      // Needed for #define of NULL
#include "SmartAlloc.h"  // MUST be included after stdlib.h

/* YOU MUST #include SmartAlloc.h IN YOUR SOLUTION (Problem3.c) FILE!
 *
 * You may do so explicitly or, indirectly, by #including this header file.
 */

/* The structure used for the linked list */
typedef struct Node {
   float value;
   struct Node *next;
} Node;

/* Adds the value to the linked list at the specfied index.
 *
 *   - Nodes in the list must be allocated from the heap.
 *   - When *head is NULL a new list is created.
 *   - You may assume the index is valid - no error handling required.
 *   - When creating a new list (*head is NULL) the index will be zero.
 *   - The index will be zero when adding to the front of an existing list.
 *   - The index will be equal to the size of the list when adding to the end
 *     of an existing list.
 *
 * Returns void
 */
void addAtIndex(Node **head, int index, float value);

/* Gets the specified value from the specified list.
 *
 *   - You may assume head is valid - no error handling required.
 *   - You may assume index is valid - no error handling required.
 *
 * Returns the value of the specfied node in the list.
 */
float getAtIndex(Node **head, int index);

/* Removes the specified node from the specified list.
 * 
 *   - The *head must be set to NULL when the list becomes empty.
 *   - The memory associated with removed node must be freed.
 *   - You may assume head is valid - no error handling required.
 *   - You may assume index is valid - no error handling required.
 *   
 * Returns void
 */
void removeAtIndex(Node **head, int index);

#endif
