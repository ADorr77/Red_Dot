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
	// int type; Possible way to implement multiple types of enemies with enum
public:
	// Monster constructor (pass in whatever you decide)
	Monster();
	// update method
	void update();

	// get Functions
	double get_strength() const;
	double get_health() const;
	double get_xPos() const;
	double get_yPos() const;

	// Write additional behavior
};

#endif