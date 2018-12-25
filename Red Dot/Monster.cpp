#include "Monster.h"
#include<cmath>
#include<ctime>

Monster::Monster()
{
	xPos = 13 + (rand()%5-3);
	yPos = 10 + (rand() % 5- 3);
	damage = 1;
	health = 10;
	hitbox = 1;
	Vel = 0.05;
	exp = 10;
}

Monster::Monster(int mapSize, double vel) {
	xPos = (mapSize/2) + (rand()%(int)(mapSize/2) - mapSize/2);
	yPos = (mapSize / 2) + (rand() % (int)(mapSize / 2) - mapSize / 2);
	damage = 2;
	health = 15;
	hitbox = 0.5;
	Vel = vel;
	exp = 10;
}

void Monster::render(Graphics* pGraphics)
{
	pGraphics->drawRegularPolygon(30, 0.3f, 0.0f, xPos, yPos, 1.0f, 0.0f, 0.0f);
}


void Monster::take_damage(double attack) {
	health -= attack;
}

void Monster::move(double X, double Y) {
	// X and Y are the Hero's X and Y coordinates
	double dist = sqrt((pow((xPos - X), 2)) + (pow((yPos - Y), 2)));

	// First if checks if monster in range to detect hero
	if (dist <= 15) {
		xPos += (1 / dist) * (X - xPos) * Vel;
		yPos += (1 / dist) * (Y - yPos) * Vel;
	}
}


double Monster::attack(double x, double y) {
	// If monster is within its hitbox range deal damage
	if (abs(xPos - x) < hitbox && abs(yPos - y) < hitbox) {
		return damage;
	}
	return 0;
}