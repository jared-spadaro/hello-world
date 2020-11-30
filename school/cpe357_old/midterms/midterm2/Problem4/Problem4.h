#ifndef PROBLEM4_H
#define PROBLEM4_H

#include "SmartAlloc.h"

/*
 * Merges the contents of two sorted arrays (ascending numerical order) into a
 * third sorted array and returns it. For example, if |a| contained {1 2 5 8}
 * and |b| contained {2 4 8 9} then result would contain {1 2 2 4 5 8 8 9}.
 *
 * IMPORTANT REQUIREMENTS:
 *
 *   1) You MAY NOT use array syntax anywhere in your solution, not even in
 *      your commments.
 *
 *   2) The returned array MUST be dynamically allocated (malloc/calloc) and
 *      be EXACTLY the size necessary to hold the merged values, no more, no
 *      less.
 *
 *   3) No data is lost, any duplicate values in one or both of the inputs
 *      are maintained.
 *
 *   4) You must #include SmartAlloc.h in YOUR .c file.
 */
int* mergeArrays(int *a, int aSize, int *b, int bSize);

#endif
