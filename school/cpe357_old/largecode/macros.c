#include <stdio.h>

#define FixMacro(m,x,y) m(x,y)

#define BadMax(x,y) x > y ? x : y

#define GoodMax(x,y) FixMacro (BadMax,x,y)


int main () {
   int a = 5, b = 7;
   BadMax(a,b);
   GoodMax(a,b);
   return 0;
}
