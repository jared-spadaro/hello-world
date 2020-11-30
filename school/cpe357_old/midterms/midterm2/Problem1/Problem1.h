/*
 * Orders the values pointed to by |a|, |b|, and |c| so that, when done,
 * the values pointed to by |a|, |b|, and |c| are in ascending numerical
 * order. For example: if, before being called, a, b, and c pointed to
 * 5.5, 3.3, and 2.2, respectively, then, after being called a, b, and c
 * would point to 2.2, 3.3, and 5.5, respectively. The function handles
 * all possible integer values, including duplicate values. For example,
 * if a, b, and c were pointing to -3.5, 7.2, -3.5, respectively, then they
 * would point -3.5, -3.5, 7.2, respectively, after the call.
 *
 * You do not need and are not expected to use any C Standard Library
 * functions in your solution.
 */
void OrderThree(float *a, float *b, float *c);
