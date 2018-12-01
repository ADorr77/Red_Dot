#pragma once

#ifndef MAPS_H
#define MAPS_H
#include "Maplib.h"


class Maps
{
private:
	char map[25][15];
public:
	Maps();
	void init_map(int mapnum);
	char get_map_value(int x, int y);
	void set_map_value(int x, int y, char c);


};

#endif