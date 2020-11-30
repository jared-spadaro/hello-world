#include "checkit.h"
#include "two.h"
#include <stdio.h>
#include "location.h"

void find_min_location_test_cases()
{
   int input[2][NUM_COLS] = {{3,2,6},{6,3,1}};
   int input_1[3][NUM_COLS] = {{5,2,7},{77,33,8},{65,4,1}};

   int num_rows = 2;
   int num_rows_1 = 3;

   int num_cols = 3;
   int num_cols_1 = 3;

   struct location index_smallest = find_min_location          (input,num_rows,num_cols);
   struct location index_smallest_1 = find_min_location(input_1,num_rows_1,num_cols_1);

   checkit_int(index_smallest.row,1);
   checkit_int(index_smallest.col,2);

   checkit_int(index_smallest_1.row,2);
   checkit_int(index_smallest_1.col,2);
}




int main (void)
{
   find_min_location_test_cases();
   return 0;
}
