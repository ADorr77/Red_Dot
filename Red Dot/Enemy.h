#pragma once

#ifndef ENEMY_H
#define ENEMY_H

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
	void advance();
	//set up timing of enemies entering
	void setTimer(int t);
	//take damage
	void takeDamage();
	// get Functions
	double get_strength() const;
	double get_health() const;
	double get_xPos() const;
	double get_yPos() const;

	// Write additional behavior
};

#endif
