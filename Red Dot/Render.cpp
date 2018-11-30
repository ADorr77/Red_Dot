#include "Render.h"

void Render::render(const TowerDefense & game)
{
	
}

void Render::render(const Dungeon& dungeon)
{
	auto map = dungeon.get_map();

	std::vector<std::string> print(map.size(), "");

	for (int x = 0; x < map.size(); x++)
	{
		for (int y = 0; y < map[0].size(); y++)
		{
			if (map[x][y] == 0)
				print[y] += (char)219;
			else
				print[y] += ' ';
		}
	}

	const std::vector<Monster>& monsters = dungeon.get_monsters();

	for (int i = 0; i < monsters.size(); i++)
	{
		print[monsters[i].get_xPos()][monsters[i].get_yPos()] = 'M';
	}

	Hero hero = dungeon.get_hero();
	print[hero.get_xPos()][hero.get_yPos()] = 'H';
}



