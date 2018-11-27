#pragma once

#ifndef ENEMY_H
#define ENEMY_H

// Generic Tower Defense Enemy
class Enemy
{
private:
	double strength;
	double health;
	double xPos, yPos;
	// int type; Possible way to implement multiple types of enemies with enum
	// double speed; could have this too potentially
public:
	// Enemy constructor (pass in whatever you decide)
	Enemy();
	// update method to move it
	void update();

	// get Functions
	double get_strength() const;
	double get_health() const;
	double get_xPos() const;
	double get_yPos() const;

	// Write additional behavior
};

#endif
