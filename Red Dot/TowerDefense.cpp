#include "TowerDefense.h"

TowerDefense::TowerDefense() {
	money = 0;
	level = 0;
	through = 0;
	lives = 100;
	m.init_map(2);
	state = 0;
	button_state = 0;
	create_tower(8, 5, 0);
	create_tower(15, 10, 1);
	create_tower(18, 7, 2);
}


int TowerDefense::processEvents(GLFWwindow * window)
{
	double x_pos, y_pos;
	glfwGetCursorPos(window, &x_pos, &y_pos);
	int click = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	if (click == GLFW_PRESS) {
		int x = (int)x_pos / 32;
		int y = (int)y_pos / 32;
		if (button_state == 0 && money >= 1000 && y<15) {
			money -= 1000;
			create_tower(x, y, 2);
		}
		if (x >= 0 && y >= 15 && x < 5 && y < 20) {
			if (state == 1) {
				state = 3;
			}
			if (state == 2) {
				state = 0;
			}
			else { state = 1; }
		}
	}
	return 0;
}

int TowerDefense::update()
{
	switch (state) {
	case 0:
		init_level();
		++level;
		++state;
		m.init_map(2);
		renderAscii();
		break;
	case 1:
		m.init_map(2);
		map_towers();
		advance_enemies();
		advance_projectiles();
		if (enemies.size() == 0) { state = 2; }
		std::cout << "Money: " << get_money() << "\t\t got thru: " << thru() << "\t\t lives: " << get_lives() << std::endl;
		renderAscii();
		break;
	case 2:
		std::cout << "\n\n\n\t end level \n\t money: " << get_money() <<
			"\n\t " << thru() << " enemies got through" << "\n\t Lives:" << get_lives();
		break;

		//pause state
	case 3:
		std::cout << "Money: " << get_money() << "\t\t got thru: " << thru() << "\t\t lives: " << get_lives() << std::endl;
		renderAscii();
		break;
	}

	return 0;
}

void TowerDefense::init_level()
{
	switch (level) {
	case 0:
		make_wave(0, 10, 1, 20);
		break;
	case 1:
		make_wave(0, 15, 5, 1);
		//make_wave(100, 20, 2, 5);
		break;
	}
}

void TowerDefense::renderAscii() {
	std::cout << std::endl;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 25; j++) {
			std::cout << m.get_map_value(j,i) << m.get_map_value(j,i);
		}
		std::cout << std::endl;
	}
}

void TowerDefense::advance_enemies()
{
	for (int j = 0; j < enemies.size(); ++j) {
		enemies[j].update_velocities(m);
		if (int gt = enemies[j].advance() > 0) {
			if (enemies.size() != 1) {
				enemies.erase(enemies.begin() + j);
			}
			else {
				gotThru(gt);
				std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t end level \n\t money: " << get_money() <<
					"\n\t " << thru() << " enemies got through \n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
				state = 2;
			}
			gotThru(gt);
		}
		for (int t = 0; t < towers.size(); ++t) {
			towers[t].detect(enemies[j].get_xPos(), enemies[j].get_yPos());
		}
		m.set_map_value((int)enemies[j].get_xPos(), (int)enemies[j].get_yPos(), 'e');

	}
}

void TowerDefense::map_towers()
{
	for (int i = 0; i < towers.size(); ++i) {
		m.set_map_value(towers[i].get_xPos(), towers[i].get_yPos(), 't');
		towers[i].cool();
	}
	
}

void TowerDefense::create_tower(int x, int y, int type)
{
	Tower *t1 = new Tower(x, y, type);
	towers.push_back(*t1);
}

void TowerDefense::towers_detect()
{
	for (int j = 0; j < towers.size(); ++j) {

	}
}

void TowerDefense::advance_projectiles()
{
	for (int t = 0; t < towers.size(); t++) {


		int c = towers[t].get_pnumber();
		while (c > 0) {
			if (!towers[t].advanceProjectiles(c - 1)) {

				//towers[t].eraseProjectile(c - 1);
				//--c;
				//if (towers[t].get_pnumber()) { --c; }
				double x = towers[t].get_projectile_x(c - 1);
				double y = towers[t].get_projectile_y(c - 1);
				m.set_map_value((int)x, (int)y, '.');
				if (!enemies.size()) { state = 2; }
				for (int j = 0; j < enemies.size(); ++j) {
					if (enemies[j].detect(x, y)) {
						towers[t].eraseProjectile(c - 1);
						enemies[j].hit_response(towers[t].get_strength());
					}
					// enemies[j].take_damage(x, y);
					if (enemies[j].get_hp() <= 0) {
						add_money(enemies[j].get_reward());
						enemies.erase(enemies.begin() + j);
						j = enemies.size();
					}

				}
			}
			else { towers[t].eraseProjectile(c - 1); }
			--c;
		}
	}
}

void TowerDefense::add_money(int m)
{
	money += m;
}

int TowerDefense::get_money() const
{
	return money;
}

int TowerDefense::thru() const
{
	return through;
}

void TowerDefense::make_wave(int offset, int spacing, int type, int quantity)
{
	int prevSize = enemies.size();
	for (int i = 0; i < quantity; ++i) {
		Enemy *e = new Enemy(type);
		enemies.push_back(*e);
	}
	for (int i = 0; i < quantity; ++i) {
		enemies[(prevSize + i)].setTimer(offset + (i*spacing));
	}
}

int TowerDefense::get_lives() const
{
	return lives;
}



/*std::vector<Projectile> TowerDefense::get_projectiles() const
{
	return projectiles;
}
*/



int TowerDefense::get_map_value(int x, int y)
{
	if (x > -1 && x<25 && y>-1 && y < 15) {
		return m.get_map_value(x, y);
	}
	return -1;
}

void TowerDefense::mapinit() {
	for (int i = 0; i < 15; i++) {
		//set up blank map
		for (int j = 0; j < 25; j++) {
			map[j][i] = m.get_map_value(j, i);
		}
	}





}

void TowerDefense::mapSet(int x, int y, char c)
{
	if (x >= 0 && x < 25 && y >= 0 && y < 15) {
		map[x][y] = c;
	}
}

void TowerDefense::mapconstSet()
{
	for (int i = 0; i < 15; ++i) {
		for (int j = 0; j < 25; ++j) {
			mapconst[j][i] = map[j][i];
		}
	}
}

void TowerDefense::gotThru(int i)
{
	through += i;
	lives -= i;
}


