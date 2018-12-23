#include "Maps.h"

Maps::Maps()
{
	map[0][0] = 0;
}

void Maps::init_map(int mapnum)
{

	for (int j = 0; j < 25; ++j) {
		for (int i = 0; i < 15; ++i) {
			if (mapnum == 1) {
				if (Maplib_map_1[i][j]) {
					map[j][i] = ' ';
				}
				else {
					map[j][i] = -37;
				}
			}
			if (mapnum == 2) {
				if (Maplib_map_2[i][j]) {
					map[j][i] = ' ';
				}
				else {
					map[j][i] = -37;
				}
			}
			if (mapnum == 3) {
				if (Maplib_map_3[i][j]) {
					map[j][i] = ' ';
				}
				else {
					map[j][i] = -37;
				}
			}
			if (mapnum == 4) {
				if (Maplib_map_4[i][j]) {
					map[j][i] = ' ';
				}
				else {
					map[j][i] = -37;
				}
			}
			if (mapnum == 5) {
				if (Maplib_map_5[i][j]) {
					map[j][i] = ' ';
				}
				else {
					map[j][i] = -37;
				}
			}
		}
	}
}

char Maps::get_map_value(int x, int y)
{
	return map[x][y];
}

void Maps::set_map_value(int x, int y, char c)
{
	map[x][y] = c;
}
