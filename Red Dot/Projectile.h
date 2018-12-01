#pragma once

#ifndef PROJECTILE_H
#define PROJECTILE_H

class Projectile
{
private:
	double xPos, yPos;
	double xVel, yVel;
	int power;
	// double radius; for different sized projectiles?
	// int type; Possible way to implement multiple types of towers with enum

public:
	// Tower constructor (pass in whatever you decide)
	Projectile(int p);
	Projectile(double x, double y, double xV, double yV, int p);
	// update method to move it
	int advance();
	//set values when firing from tower
	void setVals(double x, double y, double xV, double yV, int p);
	//getters
	double get_xPos() const { return xPos; }
	double get_yPos() const { return yPos; }
	double get_xVel() const { return xVel; }
	double get_yVel() const { return yVel; }
	double get_power() const { return power; }

	// Write additional behavior
};

#endif
