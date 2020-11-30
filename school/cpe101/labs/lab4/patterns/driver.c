#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* Include prototype for function written by student */
#include "letter.h"

#define MAX 80 /* The maximum number of rows and columns supported */


/* Local Prototypes */
static void readPattern(char pattern[MAX][MAX], int *rows, int *cols);
static int readRow(char pattern[MAX][MAX], int row, int *cols);
static void callStudent(char pattern[MAX][MAX], int rows, int cols);
static void displayResults(char pattern[MAX][MAX],
                           char student[MAX][MAX],
                           int rows,
                           int cols);

int main()
{
   char pattern[MAX][MAX];
   char student[MAX][MAX];
   int rows, cols;

   readPattern(pattern, &rows, &cols);
   callStudent(student, rows, cols);
   displayResults(pattern, student, rows, cols);

   return 0;
}

/* Reads in the pattern via redirection and stdin.
 *
 * Parameters:
 *
 *   p - Array to put the expected pattern in.
 *   r - Pointer to variable to put the number of rows in.
 *   c - Pointer to variable to put the number of columns in.
 *
 * Return: n/a   
 *
 * Special Notes:
 *
 *   Exits on following error conditions:
 *      - If pattern larger than MAX rows or columns
 *      - If any row is longer or shorter than the first row
 *      - If any letter in the pattern is not A-Z, inclusive and case sensitive!
 */
static void readPattern(char p[MAX][MAX], int *rows, int *cols)
{
   int rtrn;

   *rows = *cols = 0;

   while ((rtrn = readRow(p, *rows, cols)) > -1)
   {
      *rows = rtrn;
   }
}

/* Reads a row from stdin into the pattern array.
 *
 * Parameters:
 *
 *      p - Array to put the expected pattern in.
 *    row - Row index to populate.
 *   cols - Pointer to variable to put the number of columns in
 *          (first row only, then used to verify row lengths).
 *
 * Return: The number of the row just read (a count, not a zero-based index).
 *         Returns a negative number when the end of the input file is reached.
 *
 * Special Notes:
 *
 *   Exits on following error conditions:
 *      - If pattern larger than MAX rows or columns
 *      - If any row is longer or shorter than the first row
 *      - If any letter in the pattern is not A-Z, inclusive and case sensitive!
 */
static int readRow(char p[MAX][MAX], int row, int *cols)
{
   char ch;
   int  col, rtrn;

   /* Read entire row into provided array */
   for (col = 0;  col < MAX && (rtrn = scanf("%c", &ch)) != EOF && ch != '\n'; col++)
   {
      if (ch < 'A' || ch > 'Z')
      {
         fprintf(stderr,
         "%s%c%s%d%s",
         "Unsupported character '", ch, "' in row", row, ", must be 'A' - 'Z'\n");
         exit(1);
      }

      p[row][col] = ch;
   }

   if (col == MAX)
   {
      fprintf(stderr, "%s%d%s\n", "Patterns greater than ", MAX, " columns are not supported\n");
      exit(1);
   }

   /* Set number of columns in first row */
   if (*cols == 0)
   {
      *cols = col;
   }
   else /* Verify all subsequent rows have same number of columns */
   {
      /* Empty row at end of file? If so, ok! */
      if (rtrn == EOF && col == 0)
      {
         return -(row + 1);
      }

      /* Check row length */
      if (col != *cols)
      {
         fprintf(stderr, "Invalid pattern, variable number of columns not supported\n");
         exit(1);
      }
   }

   return row + 1;
}

/* Calls the student's funciton for each row and column of the pattern and
 * populates the array with the returned values.
 *
 * Parameters:
 *
 *      s - Array to put the student's pattern in.
 *   rows - The number of rows
 *   cols - the number of columns
 *
 * Return: n/a
 *
 * Special Notes: n/a
 */
static void callStudent(char s[MAX][MAX], int rows, int cols)
{
   int r, c;

   for (r = 0; r < rows; r++)
   {
      for (c = 0; c < cols; c++)
      {
         s[r][c] = letter(r, c);
      }
   }
}

/* Compares the expected pattern with the pattern produced by the student's
 * logic.
 *
 * Parameters:
 *
 *      p - The expected pattern
 *      s - The student's pattern
 *   rows - The number of rows
 *   cols - the number of columns
 *
 * Return: n/a
 *
 * Special Notes:
 *
 *   If the student's logic produces the expected pattern this function
 *   displays a "success" message. Otherwise this function displays the
 *   student's pattern with all incorrect letters replaced with the lower-case
 *   equvalent. Any non A-Z characters will show as a '?'.
 *
 *   When there are errors, the function displays a key to how to iterpret any
 *   lower-case letters or '?' characters.
 */
static void displayResults(char p[MAX][MAX], char s[MAX][MAX], int rows, int cols)
{
   int r, c, matches;

   /* First check to see if student's pattern matches */
   matches = 1;

   for (r = 0; matches && r < rows; r++)
   {
      for (c = 0; matches && c < cols; c++)
      {
         matches = s[r][c] == p[r][c];
      }
   }

   if (matches)
   {
      printf("\nWell done - your logic produced the specified pattern!\n\n");
      return;
   }

   /* Doesn't match :-( */
   printf("\nNot done yet - your logic did not produce the specified pattern.\n\n");
   printf("Below you see the expected pattern on the left and your pattern\n");
   printf("on the right. Any '?' characters indicate that your code returned\n");
   printf("an unexpected character (not 'A'-'Z'). Any lower case letters\n");
   printf("indicate that you returned the upper-case equivalent but it did\n");
   printf("match the specified pattern.\n\n");
   printf("Fix your logic, recompile, and test again!\n\n");
   
   for (r = 0; r < rows; r++)
   {
      /* Expected pattern */
      for (c = 0; c < cols; c++)
      {
         printf("%c", p[r][c]);
      }

      /* Separation */
      printf("   ");

      /* Student's pattern */
      for (c = 0; c < cols; c++)
      {
         if (s[r][c] < 'A' || s[r][c] > 'Z')
         {
            printf("?");
         }
         else if (s[r][c] != p[r][c])
         {
            printf("%c", tolower(s[r][c]));
         }
         else 
         {
            printf("%c", p[r][c]);
         }
      }

      printf("\n");
   }

   printf("\n");
}
