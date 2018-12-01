#include "Monster.h"
#include<cmath>

Monster::Monster()
{
	xPos = 13;
	yPos = 10;
	strength = 5;
	health = 10;
}

void Monster::move(double X, double Y) {
	// X and Y are the Hero's X and Y coordinates
	double dist = sqrt((pow((xPos - X), 2)) + (pow((yPos - Y), 2)));

	if (dist <= 30) {
		if (int(xPos) + (X - xPos) / abs(X - xPos) == 1) {
			yPos += (Y-yPos)/(abs(Y-yPos)) * Vel;
		}
		if (int(yPos) + (Y - yPos) / abs(Y - yPos) == 1) {
			xPos += (X - xPos) / (abs(X - xPos)) * Vel;
		}
		else {
			xPos += (1 / dist) * (X - xPos) * Vel;
			yPos += (1 / dist) * (Y - yPos) * Vel;
		}
	}
	else {

	}
}

