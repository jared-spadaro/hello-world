#include "line.h"
struct line2d create_line2d (double x1, double y1, double x2, double y2)
{       struct line2d line;
	line.x1 = x1;
	line.y1 = y1;
	line.x2 = x2;
	line.y2 = y2;
	return line;
}

