#pragma once

#ifndef TOWER_H
#define TOWER_H

class Tower
{
private:
	double strenght;
	double xPos, yPos;
	// int type; Possible way to implement multiple types of towers with enum
public:
	// Tower constructor (pass in whatever you decide)
	Tower();
	// update method to fire from it
	void update();

	// getters
	double get_strength() const;
	double get_xPos() const;
	double get_yPos() const;

	// Write additional behavior
};

#endif
