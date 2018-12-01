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
#include <thread>


void processInput(GLFWwindow * window);

typedef std::chrono::high_resolution_clock Clock;

int main()
{
	// initialize Game window and renderer
	Render renderer = Render();
	GLFWwindow * window = renderer.get_window();

	int state = 0; // change this for now to switch between modes
	TowerDefense td;
	Dungeon dungeon = Dungeon();

	renderer.init(td);
	

	//renderer.renderASCII(dungeon);

	// initialize timer variables
	auto start = Clock::now();
	auto end = start;
	int fps = 20; // change the render speed here (frames per second)
	__int64 duration, period = __int64((1.0 / fps) * 1000000000);
	

	while (!glfwWindowShouldClose(window)) 
	{
		// start timer
		start = Clock::now();

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
			td.processEvents(window);
			renderer.render(td);
			break;
		case 1:
			break;
		}

		// swap buffer to show screen
		glfwSwapBuffers(window);

		// stop timer and sleep
		end = Clock::now();
		duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
		std::this_thread::sleep_for(std::chrono::nanoseconds(period - duration));
	}

	glfwTerminate();

	return 0;
}

void processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}