#include "Tower.h"
#include<cmath>
#include<iostream>

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
		speed = 1;
	}
}

void Tower::detect(double x, double y)
{
	if (timer == 0) {
		double xdist = xPos - x;
		double ydist = yPos - y;
		double dist = sqrt(xdist*xdist + ydist * ydist);
		if (dist < range) {
			double xV = xdist * speed / dist;
			double yV = ydist * speed / dist;
			projectiles[pnumber].setVals(xPos, yPos, xV, yV, strength);
		}
		std::cout << "SHOT";
	}
}
