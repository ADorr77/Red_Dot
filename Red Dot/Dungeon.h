#pragma once

#ifndef DUNGEON_H
#define DUNGEON_H
#include <vector>
#include "Projectile.h"
#include "Monster.h"
#include "Hero.h"
#include <array>

class Dungeon
{
private:
	// first number is height, second is width so access is map[x][y]
	std::array<std::array<int, 20>, 20> map;
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
	const auto& get_map() const { return map; }
	const Hero& get_hero() const { return hero; }
	const std::vector<Monster>& get_monsters() const { return monsters; }
	const std::vector<Projectile>& get_projectiles() const { return projectiles; }

	// add other functionality as needed
};

#endif
