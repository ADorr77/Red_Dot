#include"Hero.h"
#include<cmath>

Hero::Hero()
{
	maxHealth = 100;
	health = maxHealth;
	level = 1;
	exp = 0;
	xPos = 10;
	yPos = 10;
	Vel = 5;
}


Hero::Hero(double level) {
	maxHealth = 100 + (10 * level);
	health = maxHealth;
	this->level = level;
	exp = 0;
	xPos = 0;
	yPos = 0;
	Vel = 5;
}

void Hero::update() {

}

void Hero::move() {
	if (xDir && yDir) {
		xPos += (Vel) / (sqrt(2));
		yPos += (Vel) / (sqrt(2));
	}
	else {
		xPos += Vel * xDir;
		yPos += Vel * yDir;
	}
}

double take_Damage(double attack) { return 0; }



