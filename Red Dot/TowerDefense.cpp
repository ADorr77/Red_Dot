#include "TowerDefense.h"
#include "Enemy.h"

TowerDefense::TowerDefense() {
	money = 1000;
	level = 0;
	through = 0;
	lives = 100;
	m.init_map(2);
	state = 2;
	button_state = 0;
	mouse_cooldown = 0;
	
}


int TowerDefense::processEvents(GLFWwindow * window)
{
	if (mouse_cooldown) { --mouse_cooldown; }
	double x_pos, y_pos;
	glfwGetCursorPos(window, &x_pos, &y_pos);
	int click = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	if (click == GLFW_PRESS && mouse_cooldown == 0) {
		mouse_cooldown = 5;
		int x = (int)x_pos / 32;
		int y = (int)y_pos / 32;
		int isOccupied = -1;
		for (int t = 0; t < towers.size(); ++t) {
			if (x == towers[t].get_xPos() && y == towers[t].get_yPos()) { isOccupied = t; }
		}
		//placing / upgrading towers
		if (button_state == 1 && money >= 500 && y<15 && isOccupied == -1) {
			money -= 500;
			create_tower(x, y, 0);
		}
		if (button_state == 2 && money >= 800 && y < 15 && isOccupied == -1) {
			money -= 800;
			create_tower(x, y, 1);
		}
		if (button_state == 3 && money >= 1500 && y < 15 && isOccupied == -1) {
			money -= 1500;
			create_tower(x, y, 2);
		}
		if (button_state == 4 && money >= 1000 && y < 15 && isOccupied == -1) {
			money -= 1000;
			create_tower(x, y, slow_t);
		}
		//play pause
		if (x >= 0 && y >= 15 && x < 5 && y < 20) {
			if (state == 1) {
				state = 3;
			}
			else if (state == 2) {
				state = 0;
			}
			else if (state == 3 ) { state = 1; }
		}
		if (x >= 0 && y >= 20 && x < 5 && y < 25) {
			return 1;
		}
		// making towers buttons
		if (x >= 5 && y >= 15 && x < 10 && y < 20) {
			button_state = 1;
		}
		if (x >= 5 && y >= 20 && x < 10 && y < 25) {
			button_state = 2;
		}
		if (x >= 10 && y >= 15 && x < 15 && y < 20) {
			button_state = 3;
		}
		if (x >= 10 && y >= 20 && x < 15 && y < 25) {
			button_state = 4;
		}
	}
	return 0;
}

int TowerDefense::update(int fps)
{
	switch (state) {
	case 0:
		init_level();
		++level;
		++state;
		m.init_map(2);
		//renderAscii();
		break;
	case 1:
		m.init_map(2);
		map_towers();
		advance_enemies(fps);
		if (state == 1){ advance_projectiles(fps); }
		if (enemies.size() == 0) { 
			clear_Projectiles();
			state = 2;
		}
		//std::cout << "Money: " << get_money() << "\t\t got thru: " << thru() << "\t\t lives: " << get_lives() << std::endl;
		//renderAscii();
		break;
	case 2:
		std::cout << "\n\n\n\t end level \n\t money: " << get_money() <<
			"\n\t " << thru() << " enemies got through" << "\n\t Lives:" << get_lives();
		break;

		//pause state
	case 3:
		std::cout << "Money: " << get_money() << "\t\t got thru: " << thru() << "\t\t lives: " << get_lives() << std::endl;
		//renderAscii();
		break;
	}

	return 0;
}

void TowerDefense::init_level()
{
	// make_wave(offset, spacing, type, quantity);
	switch (level) {
	case 0:
		make_wave(0, 10, normal, 10);
		break;
	case 1:
		make_wave(0, 15, normal, 10);
		make_wave(150, 20, strong, 5);
		break;
	case 2:
		make_wave(0, 15, normal, 20);
		make_wave(250, 20, fast, 5);
		break;
	case 3:
		make_wave(0, 15, normal, 20);
		make_wave(250, 20, tank, 5);
		break;
	case 4:
		make_wave(0, 15, normal, 10);
		make_wave(150, 20, strong, 10);
		make_wave(200, 20, fast, 10);
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

void TowerDefense::clear_Projectiles()
{
	for (int j = 0; j < towers.size(); ++j) {
		towers[j].clear_p();
	}
}

void TowerDefense::advance_enemies(int fps)
{
	for (int j = 0; j < enemies.size(); ++j) {
		enemies[j].update_velocities(m);
		if (int gt = enemies[j].advance(fps) > 0) {
			gotThru(enemies[j].get_strength());
			if (enemies.size() != 0) {
				enemies.erase(enemies.begin() + j);
			}
			else {
				//gotThru(enemies[j].get_strength());
				std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t end level \n\t money: " << get_money() <<
					"\n\t " << thru() << " enemies got through \n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
				clear_Projectiles();
				state = 2;
			}
			//gotThru(enemies[j].get_strength());
		}
		else {
			for (int t = 0; t < towers.size(); ++t) {
				towers[t].detect(enemies[j].get_xPos(), enemies[j].get_yPos());
			}
			//m.set_map_value((int)enemies[j].get_xPos(), (int)enemies[j].get_yPos(), enemies[j].get_type_char());

			// handle slow tower things -- would like to move out of td.cpp if possible but can't right now
			if (enemies[j].get_slow_timer() > 0) { enemies[j].decrement_slow(); } // count down the slow timer if enemy is being slowed.
			if (enemies[j].get_slow_timer() == 1) // resets velocities once slow_timer is down.
			{
				enemies[j].reset_speed();
			}
		}
	}
}

void TowerDefense::map_towers()
{
	for (int i = 0; i < towers.size(); ++i) {
		//m.set_map_value(towers[i].get_xPos(), towers[i].get_yPos(), 't');
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

void TowerDefense::advance_projectiles(int fps)
{
	for (int t = 0; t < towers.size(); t++) {


		int c = towers[t].get_pnumber();
		while (c > 0) {
			if (!towers[t].advanceProjectiles((c - 1), fps)) {

				//towers[t].eraseProjectile(c - 1);
				//--c;
				//if (towers[t].get_pnumber()) { --c; }
				double x = towers[t].get_projectile_x(c - 1);
				double y = towers[t].get_projectile_y(c - 1);
				//m.set_map_value((int)x, (int)y, '.');
				if (!enemies.size()) { state = 2; }
				for (unsigned int j = 0; j < enemies.size(); ++j) {
					if (enemies[j].detect(x, y)) {
						enemies[j].hit_response(towers[t].get_strength());
						if (towers[t].get_pnumber() >= 1) {
							towers[t].eraseProjectile(c - 1);
						}
					}
					if (enemies[j].get_hp() <= 0) {
						add_money(enemies[j].get_reward());
						enemies.erase(enemies.begin() + j);
//						j = enemies.size();
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
	through += 1;
	lives -= i;
}


