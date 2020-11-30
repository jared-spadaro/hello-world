#include <stdio.h>
#include "checkit.h"
#include "monster.h"

void test_cases(void)
{
	struct monster mon;
	mon = create_monster(1,2,2.5,3);
	checkit_int(mon.eyes, 1);
	checkit_int(mon.arms, 2);
	checkit_double(mon.height, 2.5);
	checkit_int(mon.tails, 3);
}

int main(int argc, char **argv)
{
   test_cases();

   return 0;
}
