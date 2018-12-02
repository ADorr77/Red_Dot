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
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		int yMove = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		int yMove = -1;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		int xMove = -1;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		int xMove = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		hero.switch_Weapon();
	}
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		return 2;
	}
	return 1;
}

int Dungeon::update() {
	for (int m = 0; m < monsters.size(); m++) {
		monsters[m].move(hero.get_xPos(), hero.get_yPos());
		hero.take_damage(monsters[m].attack(hero.get_xPos(), hero.get_yPos()));
	}
	for (int b = 0; b < bolts.size(); b++) {
		bolts[b].move();
		for (int m = 0; m < monsters.size(); m++) {
			if (bolts[b].check_hit(monsters[m].get_xPos(), monsters[m].get_yPos())) {
				monsters[m].take_damage(bolts[b].get_damage());
				bolts.erase(bolts.begin() + b);
			}
		}
		/*if (map[bolts[b].get_yPos()][bolts[b].get_xPos] == 1) {
			bolts.erase(bolts.begin() + b);
		}*/
	}
	if (monsters.size()) {
		return 1;
	}

	return 0;
}

void Dungeon::test() {
	int x;
	std::cin >> x;
	if (x == 1) {
		hero.move(1, -1);
		hero.set_direction(monsters[1].get_xPos(), monsters[1].get_yPos());
		bolts.emplace_back(hero.ranged_attack());
		bolts[0].move();
		monsters[1].take_damage(hero.melee_attack(monsters[1].get_xPos(), monsters[1].get_yPos()));
		if (monsters[1].get_health() < 10) {
			std::cout << "You got one" << std::endl;
		}
	}
	//bolts[0].move();
	/*if (bolts[0].check_hit(monsters[1].get_xPos(), monsters[1].get_yPos())) {
		std::cout << "The Bolt hit one!!!!!!!" << std::endl;
	}
	*/
	if (x = 2) {
		for (int y = 0; y < monsters.size(); y++) {
			monsters[y].move(hero.get_xPos(), hero.get_yPos());
		}
	}
	
}

