#include "two.h"
#include "location.h"

struct location find_min_location(int input[][NUM_COLS], int num_rows, int num_cols)
{
   int i,j;
   int mindex_row,mindex_col;
   if(num_rows<1 || num_cols<1)
   {
      mindex_row = -1;
      mindex_col = -1;
   }
   for(i=0;i<num_rows;i++)
   {
      for(j=0;j<num_cols;j++)
      {
         if(input[mindex_row][mindex_col] > input[i][j])
         {
            mindex_row = i;
            mindex_col = j;
            
         }
      }
   }
   struct location index_smallest = {mindex_row,mindex_col};
   return index_smallest;
}
      
