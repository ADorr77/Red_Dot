#pragma once

#ifndef MONSTER_H
#define MONSTER_H
#include "Graphics.h"

// Generic Dungeon Crawler Enemy
class Monster
{
private:
	double damage;
	double health;
	double xPos, yPos;
	double Vel;
	double hitbox;
	double exp;
	// int type; Possible way to implement multiple types of enemies with enum
public:
	// Monster constructor (pass in whatever you decide)
	Monster();
	Monster(int mapSize, double vel);
	// update method
	void update();
	// render method
	void render(Graphics * pGraphics);
	// get Functions
	double get_damage() const { return damage; }
	double get_health() const { return health; }
	double get_xPos() const { return xPos; }
	double get_yPos() const { return yPos; }
	double get_Vel() const { return Vel; }
	double get_hitbox() const { return hitbox; }
	double get_exp() const { return exp; }

	int get_xCoord() const { return (int)xPos; }
	int get_yCoord() const { return (int)yPos; }

	// Write additional behavior
	void move(double HeroX, double HeroY);

	void take_damage(double attack);

	double attack(double HeroX, double HeroY);

};

#endif