#pragma once

#ifndef RENDER_H
#define RENDER_H
#include "TowerDefense.h"
#include "Dungeon.h"
#include "Includes.h" // this gets around an glad.h issue
#include "Shader.h"

#define MAX_SIDES 25

class Render
{
private:
	GLFWwindow * window;

	unsigned int mapVAO, mapVBO, mapEBO; // Vertex Array Object for the map
	unsigned int numMapPoints; // number of verticies that make up map

	unsigned int buttonVAO, buttonVBO, buttonEBO; // Vertex Array Object for the map
	unsigned int numButtonPoints; // number of verticies that make up map
	

	unsigned int shapesArray[MAX_SIDES - 2];
	unsigned int shapesBuffer[MAX_SIDES - 2];
	unsigned int shapesElements[MAX_SIDES - 2];

	Shader shader;

public:
	// creates the map and sets up the array of polygon VAOs
	Render();

	// initialize for the different game types to send the map to the GPU
	void init(Dungeon& game);
	void init(TowerDefense& game);

	// render methods
	void render(const TowerDefense& game);
	void renderASCII(const Dungeon& dungeon);

	void drawPolygon(int sides);

	// getters
	GLFWwindow * get_window() { return window; }
};

#endif
