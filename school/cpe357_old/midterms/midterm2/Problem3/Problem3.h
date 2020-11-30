#ifndef PROBLEM3_H
#define PROBLEM3_H 

#include "SmartAlloc.h"

/* Creates and returns a new string allocated on the heap (malloc/calloc). The
 * new string is the result of inserting string |b| into string |a| at the
 * specfied index |at| - no data is lost. For example, if |a| is "This sy!", |b|
 * is "is ea", and |at| is 5 then the resulting string would be "This is easy!".
 *
 * IMPORTANT REQUIREMENTS:
 *
 *  1) Pointer syntax only - you MAY NOT use array syntax in your soluiton.
 *
 *  2) You MAY NOT use any loops in your solution - you must use C Standard
 *     Library functions to solve the problem. You MAY use the Unix man pages
 *     and the C language reference linked to the midterm web page.
 * 
 *  3) You MUST #include SmartAlloc.h in YOUR .c file.
 *
 *  4) You MUST allocate the EXACT amount of memory necessary to combine the
 *     two input strings and return it as a string, no more, no less.
 */
char* insert(const char* a, const char* b, int at);

#endif
