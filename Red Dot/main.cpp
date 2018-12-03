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
#include<Sound/irrKlang.h>

// create main sound engine
irrklang::ISoundEngine *SoundEngine = irrklang::createIrrKlangDevice();

void processInput(GLFWwindow * window);

typedef std::chrono::high_resolution_clock Clock;

int main()
{
	// initialize Game window and renderer
	Render renderer = Render();
	GLFWwindow * window = renderer.get_window();

	int state = 0; // change this for now to switch between modes
	TowerDefense td;
	Dungeon dungeon = Dungeon(1);
	
	// initialize timer variables
	auto start = Clock::now();
	auto end = start;
	int fps = 60; // change the render speed here (frames per second)
	__int64 duration, period = __int64((1.0 / fps) * 1000000000);
	
	// play theme_music
	SoundEngine->play2D("theme_music.mp3", true); 

	while (!glfwWindowShouldClose(window)) 
	{
		// start timer
		start = Clock::now();
		// SoundEngine->play2D("theme_music.mp3", true);
		// input
		glfwPollEvents();
		processInput(window);
		
		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		bool dungeon_creator = false;
		bool td_creator = false;

		switch (state)
		{
		case 0:
			for (td_creator = true; td_creator; td_creator = false) {
				renderer.init(td);
			}
			system("cls");
			state = td.update(fps);
			if (!state) { state = td.processEvents(window); }
			renderer.render(td);
			break;
		case 1:
			for (dungeon_creator = true; dungeon_creator; dungeon_creator = false) {
				dungeon.createMonsters(td.thru());
				renderer.init(dungeon);
			}
			system("cls");
			std::cout << "Health: " << dungeon.get_hero().get_health() << std::endl;
			std::cout << "Weapon: " << (dungeon.get_hero().get_weapon() == 0 ? "Magic Missile" : "Sword") << std::endl;
			int p = dungeon.processInput(window, fps);
			int u = dungeon.update(fps);
			if (p == 2) {
				std::this_thread::sleep_for(std::chrono::milliseconds(10000));
			}
			if (p == 0 || u == 0) {
				std::cout << "You've completed the level!" << std::endl;
				state = 0;
				dungeon_creator = true;
				td_creator = true;
				std::this_thread::sleep_for(std::chrono::milliseconds(10000));
				break;

			}
			if (u == 2) {
				std::cout << "You died. Game Over." << std::endl;
				renderer.render(dungeon);
				std::this_thread::sleep_for(std::chrono::milliseconds(10000));
				break;
			}
			renderer.render(dungeon);
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