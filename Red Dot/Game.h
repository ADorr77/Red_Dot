#pragma once

#ifndef GAME_H
#define GAME_H

enum GameState
{
	TOWER_DEFENSE_MODE,
	DUNGEON_CRAWLER_MODE,
	PAUSED,
	MENU //implement this state last
};

enum Errors
{
	SUCCESS,
	FAIL // generic fail, please provide more detail with other error codes
	// Add error codes here 
};

class Game
{
private:
	// the state the game is currently in using GameState enum
	int state;
	// add more game info here 

	// add game objects here
public:
	Game();
	// updates the game and return any error codes
	int update();
	// render the game and return any error codes
	int render();
};

#endif
