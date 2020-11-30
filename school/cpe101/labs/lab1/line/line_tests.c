#include "line.h"
#include <stdio.h>
#include "checkit.h"

void test_cases(void)
{
	struct line2d line;
	line = create_line2d(1.0, 2.0, 3.0, 4.0);
	checkit_double(line.x1, 1.0);
	checkit_double(line.y1, 2.0);
	checkit_double(line.x2, 3.0);
	checkit_double(line.y2, 4.0);	
}

int main(int argc, char **argv)
{
   test_cases();

   return 0;
}
