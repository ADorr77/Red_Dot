#include "Dungeon.h"
#include<chrono>
#include<thread>

Dungeon::Dungeon(int level, Graphics * pGraphics)
{
	hero = Hero(level, map.size());
	

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
	m_pGraphics = pGraphics;
}

void Dungeon::loadMap()
{
	m_pGraphics->clearMap();
	std::vector<std::vector<int>> vciMap(map.size(), std::vector<int>(map[0].size(), 0));
	
	for (int x = 0; x < map.size(); x++)
	{
		for (int y = 0; y < map[0].size(); y++)
		{
			vciMap[x][y] = map[x][y];
		}
	}

	std::vector<float> vcfMapElement = {
		0.1, 0.1,
		1.0, 0.0,
		1.0, 1.0,
		0.0, 1.0
	};
	std::vector<unsigned int> vciElementIndices = { 0,1,2,0,2,3 };
	m_pGraphics->loadMap(vciMap, 0, vcfMapElement, vciElementIndices, 0, 0, 1);
}


void Dungeon::createMonsters(int num) {
	double speed = 0.11;
	for (int i = 0; i < num; i++) {
		monsters.emplace_back(Monster(map.size(), speed));
		while (map[monsters[i].get_xPos()][monsters[i].get_yPos()] == 0) {
			monsters.erase(monsters.begin() + i);
			monsters.emplace_back(Monster(map.size(), speed));
		}
		speed += 0.025;
	}
}

int Dungeon::processInput(GLFWwindow* window, int fps) {
	static int count = 0;
	static int reload = 0;
	static int swap = 0;

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
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && swap < count) {
		swap = count + 20;
		hero.switch_Weapon();
	}

	// Pausing the Game
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		return 2;
	}

	// Orienting the Hero
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	hero.set_direction((xpos * map.size() / 800), (20 - (ypos * map.size() / 800)));

	// Processing Attacks
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && count > reload) {
		reload = count + fps/4;
		if (hero.get_weapon()) {
			for (int m = 0; m < monsters.size(); m++) {
				monsters[m].take_damage(hero.melee_attack(monsters[m].get_xPos(), monsters[m].get_yPos()));
			}
		}
		if (!hero.get_weapon()) {
			bolts.emplace_back(hero.ranged_attack());
		}
	}
	++count;
	return 1;
}

int Dungeon::update(int fps) {
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
		if (map[monsters[m].get_xCoord()][monsters[m].get_yCoord()] == 0) {
			monsters[m].move(-hero.get_xPos(), -hero.get_yPos());
			if (monsters[m].get_xCoord() + (monsters[m].get_xPos() - hero.get_xPos() / abs((monsters[m].get_xPos() - hero.get_xPos()) == 0))) {
				monsters[m].move(0, monsters[m].get_xPos() - hero.get_xPos() / abs((monsters[m].get_xPos() - hero.get_xPos())));
			}
			else if (monsters[m].get_yCoord() + (monsters[m].get_yPos() - hero.get_yPos() / abs((monsters[m].get_yPos() - hero.get_yPos()))) == 0) {
				monsters[m].move(0, monsters[m].get_yPos() - hero.get_yPos() / abs((monsters[m].get_yPos() - hero.get_yPos())));
			}
			else {
				monsters[m].move(-hero.get_xPos(), -hero.get_yPos());
			}
		}
		hero.take_damage(monsters[m].attack(hero.get_xPos(), hero.get_yPos()));
	}
	// Run through bolt functions (check_hit monsters)
	for (int b = 0; b < bolts.size(); b++) {
		for (int x = 0; x < (monsters.size()); ++x) {
			if (bolts[b].check_hit(monsters[x].get_xPos(), monsters[x].get_yPos())) {
				monsters[x].take_damage(bolts[b].get_damage());
				bolts.erase(bolts.begin() + b);
				break;
			}
		}
	}
	// Run through bolt functions (movement then hitting walls)
	for (int b = 0; b < bolts.size(); b++) {
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

void Dungeon::render()
{
	m_pGraphics->drawMap();
	hero.render(m_pGraphics);
	for (Monster monster : monsters)
	{
		monster.render(m_pGraphics);
	}
	for (Bolt bolt : bolts)
	{
		bolt.render(m_pGraphics);
	}
}

