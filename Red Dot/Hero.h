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
private:
public:
	// Hero constructor (pass in whatever you decide)
	Hero(double level);
	// update method
	void update();

	// getters
	double get_health() const;
	double get_maxHealth() const;
	double get_level() const;
	double get_exp() const;
	double get_xPos() const { return xPos; }
	double get_yPos() const { return yPos; }

	// Movement 
	double move();

	// Attacks
	double ranged_attack();
	double melee_attack();

	// Hero Damage
	double take_damage(double damage);


};

#endif
