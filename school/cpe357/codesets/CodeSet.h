/* One entry in a dictionary of codes.
 * |data| points to a contiguous block of bytes the code represents.
 * |size| is the sequence length.
 */
typedef struct Code {
   unsigned char *data;
   unsigned short size;
} Code;

/* Allocate, initialize, and return a CodeSet object, via void *
 * The CodeSet will have room for |numCodes| codes, though it will
 * initially be empty. */ 
void *CreateCodeSet(int numCodes);

/* Add a new 1-byte code to |codeSet|, returning its index, with
 * the first added code having index 0.  The new code's byte is
 * equal to |val|.  Assume (and assert, in order to pass style)
 * that there is room in the |codeSet| for a new code. */
int NewCode(void *codeSet, char val);

/* Create a new code by extending the existing code at index
 * by one zero-valued byte, using the linked structure from spec.  Any
 * existing code might be extended, not just the most recently
 * added one. Return the new code's index.  Assume |oldCode| 
 * is a valid index, and that there is enough room for 
 * a new code, but assert both of these conditions as well */
int ExtendCode(void *codeSet, int oldCode);

/* Set the final byte of the code at index |code| to |suffix|.  
 * This is used to override the zero-byte added by extendCode. 
 * If the code in question has been returned by a getCode call,
 * and not yet freed via freeCode, then the changed final byte
 * will also show in the Code data that was returned from getCode.*/
void SetSuffix(void *codeSet, int code, char suffix);

/* Return the code at index |code| */
Code GetCode(void *codeSet, int code);

/* Mark the code at index |code| as no longer needed, until a new
 * getCode call is made for that code. */
void FreeCode(void *codeSet, int code);

/* Free all dynamic storage associated with |codeSet| */
void DestroyCodeSet(void *codeSet);
