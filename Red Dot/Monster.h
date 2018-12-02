#pragma once

#ifndef MONSTER_H
#define MONSTER_H

// Generic Dungeon Crawler Enemy
class Monster
{
private:
	double damage;
	double health;
	double xPos, yPos;
	double Vel;
	double hitbox;
	// int type; Possible way to implement multiple types of enemies with enum
public:
	// Monster constructor (pass in whatever you decide)
	Monster();
	// update method
	void update();

	// get Functions
	double get_damage() const { return damage; }
	double get_health() const { return health; }
	double get_xPos() const { return xPos; }
	double get_yPos() const { return yPos; }
	double get_Vel() const { return Vel; }
	double get_hitbox() const { return hitbox; }

	// Write additional behavior
	void move(double HeroX, double HeroY);

	void take_damage(double attack);

	double attack(double HeroX, double HeroY);

};

#endif