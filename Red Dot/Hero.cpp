
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
	damage = 2;
}

Hero::Hero(double level, int mapSize) {
	maxHealth = 100 + (10 * level);
	health = maxHealth;
	this->level = level;
	exp = 0;
	xPos = mapSize/2;
	yPos = mapSize/2;
	Vel = 0.3;
	weapon = 1;
	damage = 2 + (level * 0.1);
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
	double range = 1;
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
	return Bolt::Bolt((damage-1), 0.01, (xDir), (yDir), xPos, yPos);
}

void Hero::switch_Weapon() {
	this->weapon = (weapon == 1 ? 0 : 1);
}

void Hero::take_damage(double attack) {
	health -= attack;
}

void Hero::add_exp(double xp) {
	exp += xp;
}

void Hero::level_up() {
	if (exp > (100 * (level - 0.5))) {
		maxHealth = 100 + (10 * level);
		health = maxHealth;
		level++;
	}
}

int Hero::die() {
	if (health < 0) {
		return 1;
	}
	return 0;
}

