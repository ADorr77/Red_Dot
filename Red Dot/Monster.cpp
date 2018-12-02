#include "Monster.h"
#include<cmath>

Monster::Monster()
{
	xPos = 13 + (rand()%5-3);
	yPos = 10 + (rand() % 5 - 3);
	damage = 5;
	health = 10;
	hitbox = 1;
	Vel = 1;
	exp = 10;
}

void Monster::take_damage(double attack) {
	health -= attack;
}

void Monster::move(double X, double Y) {
	// X and Y are the Hero's X and Y coordinates
	double dist = sqrt((pow((xPos - X), 2)) + (pow((yPos - Y), 2)));

	// First if checks if monster in range to detect hero
	if (dist <= 30) {
		// If typecasts xPos to int then checks if theres a wall in the direction of the hero, if so all velocity is Y
		if (int(xPos) + (X - xPos) / abs(X - xPos) == 1) {
			yPos += (Y-yPos)/(abs(Y-yPos)) * Vel;
		}
		// Same with Y here
		if (int(yPos) + (Y - yPos) / abs(Y - yPos) == 1) {
			xPos += (X - xPos) / (abs(X - xPos)) * Vel;
		}
		// Otherwise just moves towards Hero proportional to normal vector
		else {
			xPos += (1 / dist) * (X - xPos) * Vel;
			yPos += (1 / dist) * (Y - yPos) * Vel;
		}
	}
	else {

	}
}


double Monster::attack(double x, double y) {
	// If monster is within its hitbox range deal damage
	if (abs(xPos - x) < hitbox && abs(yPos - y) < hitbox) {
		return damage;
	}
	return 0;
}