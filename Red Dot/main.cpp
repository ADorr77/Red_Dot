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

inline void sleep(double dSleepTime)
{
	std::this_thread::sleep_for(std::chrono::nanoseconds(int(dSleepTime * 1.0e9)));
}

int main()
{
	// initialize Game window and renderer
	//Render renderer = Render();
	//GLFWwindow * window = renderer.get_window();

	Graphics * pGraphics = new Graphics(800, 800);

	GLFWwindow * window = pGraphics->getWindow();

	int state = 0; // change this for now to switch between modes
	TowerDefense * td = new TowerDefense(pGraphics);
	Dungeon dungeon = Dungeon(1, pGraphics);
	bool dungeon_creator = true;
	bool td_creator = true;
	
	// initialize timer variables
	double dStartTime = glfwGetTime();
	double dEndTime = glfwGetTime();
	const int nFPS = 60;
	const double dPeriod = 1.0 / nFPS;
	double duration = 0;

	// variables for the FPS Monitor
	std::string strFPSText = "";
	double dBegin = glfwGetTime(), dDone = 0;
	double dElapsed = 0;
	int frameCounter = 0;
	
	// play theme_music
	SoundEngine->play2D("theme_music.mp3", true); 
	int counter = 0;
	while (!glfwWindowShouldClose(window)) 
	{
		// start timer
		dStartTime = glfwGetTime();

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

			state = td->update(nFPS);
			try
			{
				if (!state) { state = td->processEvents(window); }
			}
			catch (int e)
			{
				std::cout << "An exception occured. Exception Nr. " << e << std::endl;
				while (true);
				return -1;
			}
			
			//if (state) { SoundEngine->play2D("Dungeon.mp3", true); }
			
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
			int p = dungeon.processInput(window, nFPS);
			int u = dungeon.update(nFPS);
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

		
		// swap buffer to show screen
		glfwSwapBuffers(window);

		dEndTime = glfwGetTime();
		
		sleep(dPeriod - (dEndTime - dStartTime));

		if (frameCounter == 30)
		{
			dDone = glfwGetTime();
			dElapsed = dDone - dBegin;
			strFPSText = "FPS: ";
			strFPSText += std::to_string(int(30.0 / dElapsed));
			dBegin = glfwGetTime();
			frameCounter = 0;
			glfwSetWindowTitle(window, strFPSText.c_str());
		}
		frameCounter++;
		
	}

	glfwTerminate();

	return 0;
}

void processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}