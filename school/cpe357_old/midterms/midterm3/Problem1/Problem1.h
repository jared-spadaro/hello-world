#ifndef PROBLEM1_H
#define PROBLEM1_H

/* Description:
 *   Returns the value of the specified number of bit(s) at the specified
 *   location of the specified value. For example, the following call would
 *   return 0xA:
 *
 *      getBits(0x69, 2, 4)
 *
 *   NOTE: 
 *      1) There is no "complexity" requirement for this problem. This means
 *         you are not required to solve this problem with a single expression.
 *      2) Be sure to read the Restrictions and Assumptions below!
 *
 * Parameters:
 *   from: The value containing the bit(s) to get.
 *     at: The location of the bit(s) to return. An "at" of 0 would indicate
 *         starting at the right-most (least significant) bit and a value of 31
 *         would indicate the left-most (most significant) bit.
 *  count: The number of bit(s) to "get". The bit(s) to get include the "at" bit
 *         and the bit(s) to its left as specifiec by "count", i.e., toward the
 *         most-significant end.
 *
 * Return:
 *   The value of the bit(s) at the specfied location shifted to the right
 *   (least significant) end.
 *
 * Restrictions:
 *   1) You MAY NOT use any loops in your soluiton.
 *
 * Assumptions:
 *   1) You may assume "at" will be between 0 and 31, inclusive - no error
 *      checking required.
 *   2) You may assume "count" will be between 1 and 32, inclusive - no error
 *      checking required.
 *   3) You may assume "at" + "count" will be between 1 and 32, inclusive - no
 *      error checking required.
 */
int getBits(unsigned int from, int at, int count);

#endif
