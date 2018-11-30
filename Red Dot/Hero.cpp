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

double Hero::move() {
	if (xDir && yDir) {
		xPos += (Vel) / (sqrt(2, 2));
		yPos += (Vel) / (sqrt(2, 2));
	}
	else {
		xPos += Vel * xDir;
		yPos += Vel * yDir;
	}
}

double Hero::melee_attack() {

}

double Hero::ranged_attack() {

}

double Hero::take_damage(double attack) {

}


double Hero::get_health() const {
	return this->health;
}

double Hero::get_maxHealth() const {
	return this->maxHealth;
}

double Hero::get_level() const {
	return this->level;
}

double Hero::get_exp() const {
	return this->exp;
}

double Hero::get_xPos() const {
	return this->xPos;
}

double Hero::get_yPos() const {
	return this->yPos;
}
