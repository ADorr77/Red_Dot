
#include"Hero.h"
#include<cmath>
#include"Dungeon.h"
#include<iostream>

Hero::Hero()
{
	maxHealth = 100;
	health = maxHealth;
	level = 1;
	exp = 0;
	xPos = 6;
	yPos = 14;
	Vel = 5;
	weapon = 1;
}

Hero::Hero(double level) {
	maxHealth = 100 + (10 * level);
	health = maxHealth;
	this->level = level;
	exp = 0;
	xPos = 6;
	yPos = 14;
	Vel = 2;
	weapon = 1;
}

void Hero::update() {

}

void Hero::move(int x, int y) {
	// x and y are just trackers to check "wasd" moves 
	if (x && y) {
		xPos += (x) * (Vel) / (sqrt(2));
		yPos += (y) * (Vel) / (sqrt(2));
	}
	else {
		xPos += Vel * x;
		yPos += Vel * y;
	}
}

void Hero::set_direction(double x, double y) {
	// takes in cursor coordinates
	double distance = sqrt(pow(x-xPos,2) + pow(y-yPos,2));
	xDir = (x - xPos) / distance;
	yDir = (y - yPos) / distance;
}

double Hero::melee_attack(double x, double y) {
		double range = 10;
		// Distance to monster
		double distM = sqrt(pow(x - xPos, 2) + pow(y - yPos, 2));
		if (distM <= range) {
			double angle_M = atan((y - yPos) / (x - xPos));	// Monster angle
			double angle_C = atan(yDir / xDir);	// Cursor angle
			if (angle_C - (3.14159265 / 6) < angle_M && angle_C + (3.1415926535 / 6) > angle_M) {
				return 5;
			}
		}
		return 0;
}

Bolt Hero::ranged_attack() {
	return Bolt::Bolt(5, 1, (xDir), (yDir), xPos, yPos);
}

void Hero::switch_Weapon() {
	weapon = (weapon == 1 ? 2 : 1);
}

void Hero::take_damage(double attack) {
	health -= attack;
}



