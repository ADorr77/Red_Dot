#pragma once

#ifndef DUNGEON_H
#define DUNGEON_H
#include <vector>
#include "Bolt.h"
#include "Monster.h"
#include "Hero.h"
#include <array>
#include "Includes.h"
#include <iostream>

class Dungeon
{
private:
	// first number is height, second is width so access is map[y][x]
	std::array<std::array<int, 20>, 20> map;
	std::vector<Monster> monsters;
	Hero hero;
	std::vector<Bolt> bolts;

public:
	// Constructs the class the first time (only called once)
	Dungeon(int level, int num_of_monsters);
	// Resets the class for the next level (call before returning different state other than paused)
	void reset();
	// Tell the game to process input, return return game state (and other info potentially)
	int processInput(GLFWwindow* window);
	// Updates the Game each tick, returns the game state 
	int update();

	// get functions
	const auto& get_map() const { return map; }
	const Hero& get_hero() const { return hero; }
	const std::vector<Monster>& get_monsters() const { return monsters; }
	const std::vector<Bolt>& get_bolts() const { return bolts; }

	// add other functionality as needed
};

#endif
