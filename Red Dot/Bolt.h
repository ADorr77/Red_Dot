#pragma once

#ifndef BOLT_H
#define BOLT_H
#include "Graphics.h"

// Generic Dungeon Crawler Enemy
class Bolt
{
private:
	double damage;
	double Vel;
	double xVel, yVel;
	double xPos, yPos;
	double hitbox_d;

public:
	// Monster constructor (pass in whatever you decide)
	Bolt(double d, double v, double xv, double yv, double xp, double yp);
	// update method
	void move();
	// render method
	void render(Graphics * pGraphics);

	// get Functions
	double get_damage() const { return damage; }
	double get_xVel() const { return xVel; }
	double get_yVel() const { return yVel; }
	double get_xPos() const { return xPos; }
	double get_yPos() const { return yPos; }
	double get_hitbox_d() const { return hitbox_d; }

	int get_xCoord() const { return (int)xPos; }
	int get_yCoord() const { return (int)yPos; }

	// Other behavior
	int check_hit(double x, double y);
};


#endif