#pragma once

#ifndef TOWER_H
#define TOWER_H

class Tower
{
private:
	int timer;
	int cooldown;
	int pnumber;
	double strength;
	int xPos, yPos;
	double range;
	// int type; Possible way to implement multiple types of towers with enum
public:
	// Tower constructor (pass in whatever you decide)
	Tower(int x, int y, int s);
	// update method to fire from it
	void detect(double x, double y);

	// getters
	double get_strength() const;
	double get_xPos() const;
	double get_yPos() const;

	// Write additional behavior
};

#endif
