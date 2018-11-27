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
private:
	// Hero constructor (pass in whatever you decide)
	Hero();
	// update method
	void update();

	// getters
	double get_health() const;
	double get_maxHealth() const;
	double get_level() const;
	double get_exp() const;
	double get_xPos() const;
	double get_yPos() const;

	// Write additional behavior
};

#endif
