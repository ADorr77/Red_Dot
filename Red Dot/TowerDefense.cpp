#include "TowerDefense.h"

/*int TowerDefense::get_map() const
{
	return map;
}
*/

TowerDefense::TowerDefense() {
	money = 0;
	level = 0;

}

void TowerDefense::renderAscii() {
	std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << std::endl;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 25; j++) {
			std::cout << map[j][i] << map[j][i];
		}
		std::cout << std::endl;
	}
}
std::vector<Enemy> TowerDefense::get_enemies() const
{
	return enemies;
}

std::vector<Tower> TowerDefense::get_towers() const
{
	return towers;
}

std::vector<Projectile> TowerDefense::get_projectiles() const
{
	return projectiles;
}

int TowerDefense::mapValue(int x, int y) {
	if (x > -1 && x<25 && y>-1 && y < 15) {
		return map[x][y];
	}
	return -1;
}

void TowerDefense::mapinit() {
	for (int i = 0; i < 15; i++) {
		//set up blank map
		for (int j = 0; j < 20; j++) {
			map[j][i] = 219;
		}
		//set up blank sidebar for menu
		for (int j = 20; j < 25; j++) {
			map[j][i] = '-';
		}		
	}
	//set up paths and buttons on menu
	//path
	for (int i=0; i < 5; ++i) {
		map[i][11] = ' ';
	}
	for (int i = 11; i > 6; --i) {
		map[4][i] = ' ';
	}
	for (int i = 4; i > 1; --i) {
		map[i][7] = ' ';
	}
	for (int i = 7; i > 1; --i) {
		map[2][i] = ' ';
	}
	for (int i = 2; i < 18; ++i) {
		map[i][2] = ' ';
	}
	for (int i = 2; i < 14; ++i) {
		map[17][i] = ' ';
	}
	for (int i = 17; i > 12; --i) {
		map[i][13] = ' ';
	}
	for (int i = 13; i > 5; --i) {
		map[13][i] = ' ';
	}
	for (int i = 13; i > 9; --i) {
		map[i][6] = ' ';
	}
	for (int i = 6; i < 15; ++i) {
		map[9][i] = ' ';
	}
	



}

void TowerDefense::mapSet(int x, int y, char c)
{
	map[x][y] = c;
}

void TowerDefense::mapconstSet()
{
	for (int i = 0; i < 15; ++i) {
		for (int j = 0; j < 25; ++j) {
			mapconst[j][i] = map[j][i];
		}
	}
}
