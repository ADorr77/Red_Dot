#pragma once

#ifndef TOWER_DEFENSE_H
#define TOWER_DEFENSE_H
#include <vector>
#include "Enemy.h"
#include "Tower.h"
#include "Projectile.h"
#include "Maps.h"
#include<iostream>
#include "Includes.h"
#include "Button.h"
#include "Graphics.h"

class TowerDefense
{
private:
	int through;
	int level;
	int money;
	int state;
	int button_state;
	int lives;
	int print;
	int mouse_cooldown;
	char map[25][15];
	char mapconst[25][15];
	int mapnumber;
	// map that holds path that does not get changed or printed out
	Maps m;
	std::vector<Enemy> enemies;
	std::vector<Tower> towers;
	std::vector<Button> buttons;

	Graphics * m_pGraphics;
	Font * m_pFont;


public:

	// Constructs the class the first time (only called once)
	TowerDefense(Graphics * pGraphics);
	// Initializes the map, sets up path and side bar menu
	void mapinit();
	//change a value of the map
	void mapSet(int x, int y, char c);
	// sets mapconst to original map state
	void mapconstSet();
	//keeps track of how many get through
	void gotThru(int i);
	void reset_through();

	// Resets the class for the next level (call before returning different state other than paused)
	void reset();
	// Tell the game to process input, return return game state (and other info potentially)
	int processEvents(GLFWwindow * window);
	// Updates the Game each tick, returns the game state 
	int update(int fps);
	// renders game
	void render();
	//function for testing out game functionality
	void init_level();
	void renderAscii();
	void clear_Projectiles();
	//advances enemies
	void advance_enemies(int fps);
	//places towers on map
	void map_towers();
	//creates a new tower and adds to vector
	void create_tower(int x, int y, int type);
	//calls towers to detect and shoot if necessary
	void towers_detect();
	void advance_projectiles(int fps);
	// get functions

	// getters
	int mapValue(int x, int y);
	int get_map_value(int x, int y);
	const std::vector<Enemy>& get_enemies() const { return enemies; }
	const std::vector<Tower>& get_towers() const { return towers; }
	const std::vector<Button>& get_buttons() const { return buttons; }
	// add other functionality as needed
	void add_money(int m);
	int get_money() const;
	int thru();
	int get_thru();
	void make_wave(int offset, int spacing, int type, int quantity);
	int get_lives() const;

	const int height = 15;
	const int width = 25;
	void create_button(int x, int y, int s);
	void reset_buttons();
};

#endif