char letter (int row, int col)
{
   if ((col>=4 && col<=9 && row>=2 && row<=3) || (col>=4 && col<=6 && row>=4   	  && row<=5))
   {
      return 'Z';
   }
   else if (col>=7 && col<=9 && row>=4 && row<=5)
   {
      return 'X';
   }
   else if ((col>=10 && col<=12 && row>=4 && row<=5) || (col>=7 && col<=12 &&  		    row == 6))
   {
      return 'B';
   }
   else
   {
      return 'T';
   }
}
