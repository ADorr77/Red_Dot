#pragma once

#ifndef MONSTER_H
#define MONSTER_H

// Generic Dungeon Crawler Enemy
class Monster
{
private:
	double strength;
	double health;
	double xPos, yPos;
	double Vel;
	// int type; Possible way to implement multiple types of enemies with enum
public:
	// Monster constructor (pass in whatever you decide)
	Monster();
	// update method
	void update();

	// get Functions
	double get_strength() const { return strength; }
	double get_health() const { return health; }
	double get_xPos() const { return xPos; }
	double get_yPos() const { return yPos; }

	// Write additional behavior
	void move(double HeroX, double HeroZ);
};

#endif