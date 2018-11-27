#include "TowerDefense.h"

int** TowerDefense::get_map() const
{
	return map;
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
