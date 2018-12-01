#pragma once

#ifndef HERO_H
#define HERO_H
#include<vector>

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

	// Movement 
	void move();

	// Attacks
	double ranged_attack();
	double melee_attack();

	// Hero Damage
	void take_damage(double damage);


};

#endif
