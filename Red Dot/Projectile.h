#pragma once

#ifndef PROJECTILE_H
#define PROJECTILE_H

class Projectile
{
private:
	double xPos, yPos;
	double xVel, yVel;
	double power;
	// double radius; for different sized projectiles?
	// int type; Possible way to implement multiple types of towers with enum

public:
	// Tower constructor (pass in whatever you decide)
	Projectile();
	// update method to move it
	void update();

	//getters
	double get_xPos() const;
	double get_yPos() const;
	double get_xVel() const;
	double get_yVel() const;
	double get_power() const;

	// Write additional behavior
};

#endif
