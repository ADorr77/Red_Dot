#include "Tower.h"

Tower::Tower(int x, int y, int s)
{
	xPos = x;
	yPos = y;
	strength = s;
	timer = 0;
	pnumber = 0;
	if (strength == 1) {
		cooldown = 10;
		range = 5;
	}
}

void Tower::detect(double x, double y)
{
	double dist = sqrt()
	if (((xPos - x)*(xPos - x) + (yPos - y)*(yPos - y)) < (range*range) && timer = 0) {

	}
}
