#include "monster.h"

struct monster create_monster(int eyes, int arms, double height, int tails)
{
	struct monster mon;
	mon.eyes = eyes;
	mon.arms = arms;
	mon.height = height;
	mon.tails = tails;
	return mon;
}
