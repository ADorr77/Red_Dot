//
// The main of the Project which sets up the window, renderer, and game loop.
// 
// Written by Aaron Dorrance
// 11/26/18


#include "Render.h"
#include "Includes.h" // works around issue including glad.h and glfw3.h
#include"TowerDefense.h"
#include<stdlib.h>
#include "Dungeon.h"
#include <chrono>


void processInput(GLFWwindow * window);

typedef std::chrono::high_resolution_clock Clock;

int main()
{
	Render renderer = Render();
	GLFWwindow * window = renderer.get_window();

	int state = 0; // change this for now to switch between modes
	TowerDefense td;
	Dungeon dungeon = Dungeon();
	

	renderer.renderASCII(dungeon);


	while (!glfwWindowShouldClose(window)) 
	{
		// input
		glfwPollEvents();
		processInput(window);

		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		switch (state)
		{
		case 0:
			system("cls");
			td.update();
			break;
		case 1:
			break;
		}

		// swap buffer to show screen
		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}

void processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}