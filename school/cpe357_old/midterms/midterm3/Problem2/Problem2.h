#ifndef PROBLEM2_H
#define PROBLEM2_H

/* Description:
 *   Changes the specified number of bit(s) at the specified location to the
 *   specified value. For example, if setBits where called with "value" whose
 *   target was 0xAA, "at" of 3, "count" of 4, and "bitValue" of 0xE then,
 *   after the call, the target of "value" would be 0xF2.
 *
 *   NOTE: 
 *      1) There is no "complexity" requirement for this problem. This means
 *         you are not required to solve this problem with a single expression.
 *      2) Be sure to read the Restrictions and Assumptions below!
 *
 * Parameters:
 *      value: Address of target value who's bit(s) are to be set.
 *         at: The bit to modify. An "at" of 0 would indicate the right-most
 *             (least significant) bit and a value of 31 would indicate the
 *             left-most (most-significant) bit.
 *      count: The number of bits to "set". The bits to set include the "at"
 *             bit and the bit(s) to its left as specified by "count", i.e.,
 *             toward the most-significant end.
 *   bitValue: The value of the bits to set at the specfied location in value.
 *
 * Return:
 *    void
 *
 * Restrictions:
 *   1) You MAY NOT use any loops in your soluiton.
 *
 * Assumptions:
 *   1) You may assume "at" is between 0 and 31, inclusive - no error checking
 *      required.
 *   2) You may assume "count" is between 1 and 32, inclusive - no error
 *      checking required.
 *   3) You may assume that "at" + "count" is between 1 and 32, inclusive - no
 *      error checking requried.
 */
void setBits(unsigned int *value, int at, int count, unsigned int bitValue);

#endif
