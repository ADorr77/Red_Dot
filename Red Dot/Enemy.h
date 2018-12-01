#pragma once

#ifndef ENEMY_H
#define ENEMY_H
#include<cmath>
#include "Maps.h"
#include "Tower.h"

// Generic Tower Defense Enemy
class Enemy
{
private:
	int timer;
	double speed;
	double strength;
	double maxhp;
	double hp;
	int reward;
	double xPos, yPos;
	double xVel, yVel;
	// int type; Possible way to implement multiple types of enemies with enum
	// double speed; could have this too potentially
public:
	// Enemy constructor (pass in whatever you decide)
	Enemy();
	Enemy(int level);
	// update method to move it
	void update();
	// advance position
	int advance();
	//set up timing of enemies entering
	void setTimer(int t);

	//take damage
	//detect projectiles
	int detect(double x, double y);
	void take_damage();
	void hit_response(int);

	// get Functions
	double get_strength() const;
	double get_hp() const;
	double get_xPos() const;
	double get_yPos() const;
	int get_reward() const;
	double get_xVel() const;
	double get_yVel() const;
	void set_xVel(int);
	void set_yVel(int);
	void update_velocities(Maps m);
	// Write additional behavior
};

#endif
