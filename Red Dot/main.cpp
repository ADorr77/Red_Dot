//
// The main of the Project which sets up the window, renderer, and game loop.
// 
// Written by Aaron Dorrance
// 11/26/18

#define STB_IMAGE_IMPLEMENTATION
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
	//Render renderer = Render();
	//GLFWwindow * window = renderer.get_window();

	Graphics * pGraphics = new Graphics(800, 800);
	Font * font = new Font("Fonts/SmallFonts.bff");

	GLFWwindow * window = pGraphics->getWindow();

	int state = 0; // change this for now to switch between modes
	TowerDefense * td = new TowerDefense(pGraphics);
	Dungeon dungeon = Dungeon(1, pGraphics);
	bool dungeon_creator = true;
	bool td_creator = true;
	
	// initialize timer variables
	auto start = Clock::now();
	auto end = start;
	int fps = 60; // change the render speed here (frames per second)
	__int64 duration, period = __int64((1.0 / fps) * 1000000000);
	std::string strFPSText;
	double dBegin = glfwGetTime(), dDone = 0;
	double dElapsed = 0;
	int frameCounter = 0;
	
	// play theme_music
	SoundEngine->play2D("theme_music.mp3", true); 
	int counter = 0;
	while (!glfwWindowShouldClose(window)) 
	{
		// start timer
		start = Clock::now();
		// input
		glfwPollEvents();
		processInput(window);
		
		// render
		pGraphics->clear(0.0f, 0.0f, 0.0f);
		switch (state)
		{
		case 0:
			for (td_creator; td_creator; td_creator = false) {
				td->mapinit();
			}
			if (counter == 0) {
				/*system("cls");
				std::cout << "Money: " << td.get_money() << "\t\t Got through:" << td.get_thru();*/
				counter = 30;
			}
			else { --counter; }
			state = td->update(fps);
			if (state) { SoundEngine->play2D("Dungeon.mp3", true); }
			if (!state) { state = td->processEvents(window); }
			td->render();
			//renderer.render(*td);
			break;
		case 1:
			for (dungeon_creator; dungeon_creator; dungeon_creator = false) {
				dungeon.createMonsters(td->thru());
				dungeon.loadMap();
				//renderer.init(dungeon);
			}
			//system("cls");
			//std::cout << "Health: " << dungeon.get_hero().get_health() << std::endl;
			//std::cout << "Weapon: " << (dungeon.get_hero().get_weapon() == 0 ? "Magic Missile" : "Sword") << std::endl;
			int p = dungeon.processInput(window, fps);
			int u = dungeon.update(fps);
			if (p == 0 || u == 0) {
				std::cout << "You've completed the level!" << std::endl;
				state = 0;
				dungeon_creator = true;
				td_creator = true;
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				break;

			}
			if (u == 2) {
				std::cout << "You died. Game Over." << std::endl;
				SoundEngine->play2D("Sounds/you_lose.mp3", false);
				dungeon.render();
				//renderer.render(dungeon);
				std::this_thread::sleep_for(std::chrono::milliseconds(1500));
				glfwSetWindowShouldClose(window, true);
			}
			dungeon.render();
			//renderer.render(dungeon);
			break;
		}

		//pGraphics->drawText(strFPSText, *font, 0, 2, 6, 2, 0, 1, 0, 1);
		// swap buffer to show screen
		glfwSwapBuffers(window);

		// stop timer and sleep
		end = Clock::now();
		duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
		std::this_thread::sleep_for(std::chrono::nanoseconds(period - duration));
		/*if (frameCounter == 30)
		{
			dDone = glfwGetTime();
			dElapsed = dDone - dBegin;
			strFPSText = "FPS: ";
			strFPSText += std::to_string(int(30.0 / dElapsed));
			dBegin = glfwGetTime();
			frameCounter = 0;
		}
		frameCounter++;*/
		
	}

	glfwTerminate();

	return 0;
}

void processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}