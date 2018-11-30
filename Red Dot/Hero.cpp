#include"Hero.h"
#include<cmath>

Hero::Hero(double level) {
	maxHealth = 100 + (10 * level);
	health = maxHealth;
	level = level;
	exp = 0;
	xPos = 50;
	yPos = 10;
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



