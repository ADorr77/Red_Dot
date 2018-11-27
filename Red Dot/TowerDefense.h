#pragma once

#ifndef TOWER_DEFENSE_H
#define TOWER_DEFENSE_H
#include <vector>
#include "Enemy.h"
#include "Tower.h"
#include "Projectile.h"

class TowerDefense
{
private:
	int ** map;
	std::vector<Enemy> enemies;
	std::vector<Tower> towers;
	std::vector<Projectile> projectiles;

public:
	// Constructs the class the first time (only called once)
	TowerDefense();
	// Resets the class for the next level (call before returning different state other than paused)
	void reset();
	// Tell the game to process input, return return game state (and other info potentially)
	int processInput();
	// Updates the Game each tick, returns the game state 
	int update();

	// get functions
	int ** get_map() const;
	std::vector<Enemy> get_enemies() const;
	std::vector<Tower> get_towers() const;
	std::vector<Projectile> get_projectiles() const;

	// add other functionality as needed
};

#endif
