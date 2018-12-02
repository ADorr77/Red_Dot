#include "Dungeon.h"

Dungeon::Dungeon(int num)
{
	hero = Hero();
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
	bolts[0].move();
	if (bolts[0].check_hit(monsters[1].get_xPos(), monsters[1].get_yPos())) {
		std::cout << "The Bolt hit one!!!!!!!" << std::endl;
	}
	/*
	if (x = 2) {
		for (int y = 0; y < monsters.size(); y++) {
			monsters[y].move(hero.get_xPos, hero.get_yPos);
		}
	}
	*/
}

