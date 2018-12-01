#pragma once

#ifndef RENDER_H
#define RENDER_H
#include "TowerDefense.h"
#include "Dungeon.h"
#include "Includes.h" // this gets around an glad.h issue

class Render
{
private:
	GLFWwindow * window;
	
public:
	// creates the map and sets up the array of polygon VAOs
	Render();

	// initialize for the different game types to send the map to the GPU
	void init(Dungeon& game);
	void init(TowerDefense& game);

	// render methods
	void render(const TowerDefense& game);
	void renderASCII(const Dungeon& dungeon);

	// getters
	GLFWwindow * get_window() { return window; }
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#endif
