#include "Dungeon.h"

Dungeon::Dungeon(int level ,int num)
{
	hero = Hero(level);
	for (int x = 0; x < map.size(); x++)
	{
		for (int y = 0; y < map[0].size(); y++)
		{
			map[x][y] = 0;
		}
	}

	for (int x = 5; x < 15; x++)
	{
		for (int y = 5; y < 15; y++)
		{
			map[x][y] = 1;
		}
	}

	for (int i = 0; i < num; i++) {
		monsters.emplace_back(Monster());
	}
	
}
int Dungeon::processInput(GLFWwindow* window) {
	// Hero Movement
	int xMove = 0;
	int yMove = 0;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		yMove = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		xMove = -1;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		yMove = -1;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		xMove = 1;
	}
	hero.move(xMove, yMove);
	if (map[hero.get_xCoord()][hero.get_yCoord()] == 0) {
		hero.move(-xMove, -yMove);
	}

	// Switching Weapons
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		hero.switch_Weapon();
	}

	// Pausing the Game
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		return 2;
	}

	// Orienting the Hero
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	hero.set_direction(xpos, ypos);

	// Processing Attacks
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		if (hero.get_weapon() == 1) {
			for (int m = 0; m < monsters.size(); m++) {
				monsters[m].take_damage(hero.melee_attack(monsters[m].get_xPos(), monsters[m].get_yPos()));
			}
		}
		if (hero.get_weapon() == 2) {
			bolts.emplace_back(hero.ranged_attack());
		}
	}

	return 1;
}

int Dungeon::update() {
	// Run through monster death
	for (int m = 0; m < monsters.size(); m++) {
		if (monsters[m].get_health() <= 0) {
			hero.add_exp(monsters[m].get_exp());
			monsters.erase(monsters.begin() + m);
		}
	}

	// Run through monster functions (movement and attacks)
	for (int m = 0; m < monsters.size(); m++) {
		monsters[m].move(hero.get_xPos(), hero.get_yPos());
		hero.take_damage(monsters[m].attack(hero.get_xPos(), hero.get_yPos()));
	}
	// Run through bolt functions (movement and check_hit monsters and walls)
	for (int b = 0; b < bolts.size(); b++) {
		for (int x = 0; x < (monsters.size() -1); x++) {
			if (bolts[b].check_hit(monsters[x].get_xPos(), monsters[x].get_yPos())) {
				monsters[x].take_damage(bolts[b].get_damage());
				bolts.erase(bolts.begin() + b);
			}
		}
		bolts[b].move();
		if (map[bolts[b].get_xCoord()][bolts[b].get_yCoord()] == 0) {
			bolts.erase(bolts.begin() + b);
		}
		
	}
	hero.level_up();
	// If monsters exist, keep dungeon running
	if (hero.die()) {
		return 2;
	}
	if (monsters.size()) {
		return 1;
	}

	return 0;
}
