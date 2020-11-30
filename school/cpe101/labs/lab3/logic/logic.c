#include "logic.h"

int is_even (int x)
{
   return x%2 == 0;
}

int is_between (int x, int y, int z)
{
   return x>y && x<z;
}

int in_an_interval (int x)
{
   return (x>=2 && x<9) || (x>47 && x<92) || (x>12 && x<=19) || (x>=101 && x<=103);
}


