#pragma once

#ifndef HERO_H
#define HERO_H
#include<vector>
#include"Bolt.h"
#include "Graphics.h"
#include "Model.h"

class Hero
{
private:
	double health;
	double maxHealth;
	double level;
	double exp;
	double xPos, yPos;
	double Vel;
	double xDir, yDir;
	int weapon;
	double damage;
	float m_dMeleRange;
	float m_dMeleAngle;
	float m_dHeroRadius;

	Model * m_pSwordSwing;

public:
	// Hero constructor (pass in whatever you decide)
	Hero();
	Hero(double level, int mapSize);
	// update method
	void update();
	// render
	void render(Graphics * pGraphics);
	void renderAttack(Graphics * pGraphics);
	// getters
	double get_health() const { return health; }
	double get_maxHealth() const { return health; }
	double get_level() const { return level; }
	double get_exp() const { return exp; }
	double get_xPos() const { return xPos; }
	double get_yPos() const { return yPos; }
	int get_weapon() const { return weapon; }

	int get_xCoord() const { return (int)xPos; }
	int get_yCoord() const { return (int)yPos; }

	void set_weapon(int w) { this->weapon = w; }

	// Movement and Direction
	void move(int x, int y);
	void set_direction(double xH, double yH);

	// Attacks
	double melee_attack(double xM, double yM);
	Bolt ranged_attack();

	// Hero Damage
	void take_damage(double damage);

	// Technical
	void switch_Weapon();
	void add_exp(double xp);
	void level_up();
	int die();

};

#endif
