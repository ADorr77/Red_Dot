#pragma once

#ifndef HERO_H
#define HERO_H
#include<vector>
#include"Bolt.h"

class Hero
{
private:
	double health;
	double maxHealth;
	double level;
	double exp;
	double xPos, yPos;
	double Vel;
	double xDir, yDir;
	int weapon;

public:
	// Hero constructor (pass in whatever you decide)
	Hero();
	Hero(double level);
	// update method
	void update();

	// getters
	double get_health() const { return health; }
	double get_maxHealth() const { return health; }
	double get_level() const { return level; }
	double get_exp() const { return exp; }
	double get_xPos() const { return xPos; }
	double get_yPos() const { return yPos; }
	double get_weapon() const { return weapon; }

	// Movement and Direction
	void move(int x, int y);
	void set_direction(double xH, double yH);

	// Attacks
	double melee_attack(double xM, double yM);
	Bolt ranged_attack();

	// Hero Damage
	void take_damage(double damage);

	// Technical
	void switch_Weapon();

};

#endif
