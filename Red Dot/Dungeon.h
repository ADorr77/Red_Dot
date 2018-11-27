#pragma once

#ifndef DUNGEON_H
#define DUNGEON_H
#include <vector>
#include "Projectile.h"
#include "Monster.h"
#include "Hero.h"

class Dungeon
{
private:
	int ** map;
	std::vector<Monster> monsters;
	Hero hero;
	std::vector<Projectile> projectiles;

public:
	// Constructs the class the first time (only called once)
	Dungeon();
	// Resets the class for the next level (call before returning different state other than paused)
	void reset();
	// Tell the game to process input, return return game state (and other info potentially)
	int processInput();
	// Updates the Game each tick, returns the game state 
	int update();

	// get functions
	int ** get_map() const;
	Hero& get_hero() const;
	std::vector<Monster> get_monsters() const;
	std::vector<Projectile> get_projectiles() const;

	// add other functionality as needed
};

#endif
