#pragma once

#ifndef RENDER_H
#define RENDER_H
#include "TowerDefense.h"
#include "Dungeon.h"

class Render
{
public:
	Render();
	void render(const TowerDefense& game);
	void renderASCII(const Dungeon& dungeon);
};

#endif
