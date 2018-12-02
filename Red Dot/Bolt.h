#pragma once

#ifndef BOLT_H
#define BOLT_H

// Generic Dungeon Crawler Enemy
class Bolt
{
private:
	double damage;
	double Vel;
	double xVel, yVel;
	double xPos, yPos;

public:
	// Monster constructor (pass in whatever you decide)
	Bolt();
	// update method
	void move();

	// get Functions
	double get_damage() const { return damage; }
	double get_xVel() const { return xVel; }
	double get_yVel() const { return yVel; }
	double get_xPos() const { return xPos; }
	double get_yPos() const { return yPos; }

};


#endif