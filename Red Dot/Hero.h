#pragma once

#ifndef HERO_H
#define HERO_H

class Hero
{
private:
	double health;
	double maxHealth;
	double level;
	double exp;
	double xPos, yPos;
public:
	// Hero constructor (pass in whatever you decide)
	Hero();
	// update method
	void update();

	// getters
	double get_health() const;
	double get_maxHealth() const;
	double get_level() const;
	double get_exp() const;
	double get_xPos() const { return xPos; }
	double get_yPos() const { return yPos; }

	// Write additional behavior
};

#endif
