#pragma once

#ifndef ENEMY_H
#define ENEMY_H
#include<cmath>
#include "Maps.h"
#include "Tower.h"

enum { regen, normal, strong, fast, tank, boss };
// Generic Tower Defense Enemy
class Enemy
{
private:
	char type_char;
	int type; 
	int timer;
	double speed;
	double strength;
	double maxhp;
	double hp;
	int reward;
	double xPos, yPos;
	double xVel, yVel;
    int slow_timer;
	// int type; Possible way to implement multiple types of enemies with enum
	// double speed; could have this too potentially
public:
	// Enemy constructor (pass in whatever you decide)
	Enemy();
	Enemy(int level);
	// update method to move it
	void update();
	// advance position
	int advance(int fps);
	//set up timing of enemies entering
	void setTimer(int t);

	//take damage
	//detect projectiles
	int detect(double x, double y);
	void take_damage(int);
	void slow();
	void hit_response(int);

	// get Functions
	int get_type() const { return type; }
	double get_strength() const;
	double get_hp() const;
	double get_xPos() const;
	double get_yPos() const;
	int get_reward() const;
	double get_xVel() const;
	double get_yVel() const;
	double get_slow_timer() const { return slow_timer; }
	char get_type_char() const { return type_char; }
	// set functions
	void set_xVel(int);
	void set_yVel(int);
	void update_velocities(Maps m);
	void decrement_slow() { --slow_timer; } // move thsi to cpp
	void reset_speed() { speed *= 4; } // move this to cpp
	// Write additional behavior
};

#endif
