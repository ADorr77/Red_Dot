#pragma once

#ifndef TOWER_DEFENSE_H
#define TOWER_DEFENSE_H
#include <vector>
#include "Enemy.h"
#include "Tower.h"
#include "Projectile.h"
#include<iostream>
#include <glfw3.h>


class TowerDefense
{
private:
	int through;
	int level;
	int money;
	char map[25][15];
	char mapconst[25][15]; // map that holds path that does not get changed or printed out
	std::vector<Enemy> enemies;
	std::vector<Tower> towers;
	

public:
	// Constructs the class the first time (only called once)
	TowerDefense();
	// Initializes the map, sets up path and side bar menu
	void mapinit();
	//change a value of the map
	void mapSet(int x, int y, char c);
	// sets mapconst to original map state
	void mapconstSet();
	//keeps track of how many get through
	void gotThru(int i);
	
	// Resets the class for the next level (call before returning different state other than paused)
	void reset();
	// Tell the game to process input, return return game state (and other info potentially)
	int processInput(GLFWwindow window);
	// Updates the Game each tick, returns the game state 
	int update();
	//function for testing out game functionality
	void renderAscii();

	// get functions
	//int ** get_map() const;
	int mapValue(int x, int y);
	const std::vector<Enemy>& get_enemies() const { return enemies; }
	const std::vector<Tower>& get_towers() const { return towers; }

	// add other functionality as needed
	void add_money(int m);
	int get_money() const;
	int thru() const;

	const int height = 15;
	const int width = 25;
};

#endif
