char letter (int row, int col)
{
   if (row == col || row == 6 - col)
   {
      return 'X';
   }
   else 
   {
      return 'O';
   }
}
