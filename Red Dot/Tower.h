#pragma once

#ifndef TOWER_H
#define TOWER_H
#include "Projectile.h"
#include<vector>

class Tower
{
private:
	int timer;
	int cooldown;
	int pnumber;
	double strength;
	int xPos, yPos;
	double range;
	double speed;
	int price;
	std::vector<Projectile> projectiles;
	// int type; Possible way to implement multiple types of towers with enum
public:
	// Tower constructor (pass in whatever you decide)
	Tower(int x, int y, int s);
	// update method to fire from it
	void detect(double x, double y);
	int advanceProjectiles(int pnum);
	void cool();
	void eraseProjectile(int pnum);
	double get_pnumber();
	double get_projectile_x(int pnum);
	double get_projectile_y(int pnum);
	// getters
	
	double get_strength() const;
	double get_xPos() const;
	double get_yPos() const;
	const std::vector<Projectile>& get_projectiles() const { return projectiles; }
};

#endif
