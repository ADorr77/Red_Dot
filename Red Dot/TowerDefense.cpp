#include "TowerDefense.h"
#include "Enemy.h"
#include<Sound/irrKlang.h>
#include<Windows.h>

irrklang::ISoundEngine *SoundEngineTD = irrklang::createIrrKlangDevice();

TowerDefense::TowerDefense(Graphics * pGraphics) {
	money = 1500;
	level = 0;
	through = 0;
	lives = 100;
	mapnumber = 1;
	m.init_map(mapnumber);
	state = 2;
	button_state = 0;
	mouse_cooldown = 0;
	print = 0;
	m_pGraphics = pGraphics;
	m_pFont = new Font("Fonts/TimesNewRoman.bff");
	
	for (int i = 0; i < 5; ++i) {
		for (int j = 3; j < 5; ++j) {
			int s;
			if (j == 3 && i == 0) { s = 3; }
			else { s = 0; }
			create_button(i, j, s);
		}
	}
}

void TowerDefense::mapinit()
{
	m_pGraphics->clearMap();

	std::vector<std::vector<int>> vciMap(25, std::vector<int>(15, 0));

	for (int i = 0; i < 15; i++) {
		//set up blank map
		for (int j = 0; j < 25; j++) {
			
			vciMap[j][i] = m.get_map_value(j, i);;
		}
	}

	std::vector<float> vcfMapElement = {
		0.1, 0.1,
		0.9, 0.1,
		0.9, 0.9,
		0.1, 0.9
	};
	std::vector<unsigned int> vciElementIndices = { 0,1,2,0,2,3 };

	m_pGraphics->loadMap(vciMap, -37, vcfMapElement, vciElementIndices, 0, 0.5f, 0, true);
	//pGraphics->loadMap(vciMap, -37, "Resources/grass.png", true);
	m_pGraphics->loadMap(vciMap, ' ', "Resources/dirt.png", true);
}

void TowerDefense::reset()
{
	money = 1500;
	level = 0;
	through = 0;
	lives = 100;
	mapnumber += 1;
	m.init_map(mapnumber);
	state = 2;
	button_state = 0;
	mouse_cooldown = 0;
	print = 0;
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
			SoundEngineTD->play2D("Place_tower.mp3", false); // play click sound
		}
		if (button_state == 2 && money >= 800 && y < 15 && isOccupied == -1) {
			money -= 800;
			create_tower(x, y, 1);
			SoundEngineTD->play2D("Place_tower.mp3", false); // play click sound
		}
		if (button_state == 3 && money >= 2500 && y < 15 && isOccupied == -1) {
			money -= 2500;
			create_tower(x, y, 2);
			SoundEngineTD->play2D("Place_tower.mp3", false); // play click sound
		}
		if (button_state == 4 && money >= 1200 && y < 15 && isOccupied == -1) {
			money -= 1200;
			create_tower(x, y, slow_t);
			SoundEngineTD->play2D("Place_tower.mp3", false); // play click sound
		}
		//play pause
		if (x >= 0 && y >= 15 && x < 5 && y < 20) {
			if (state == 1) {
				state = 3;
				buttons[0].setState(3);
			}
			else if (state == 2) {
				state = 0;
				buttons[0].setState(4);
			}
			else if (state == 3 ) { 
				state = 1;
				buttons[0].setState(4);
			}
			SoundEngineTD->play2D("select.mp3", false);
		}
		if (x >= 0 && y >= 20 && x < 5 && y < 25) {
			return 1;
		}
		// making towers buttons
		if (x >= 5 && y >= 15 && x < 10 && y < 20) {
			button_state = 1;
			reset_buttons();
			buttons[2].setState(1);
			SoundEngineTD->play2D("select.mp3", false);
		}
		if (x >= 5 && y >= 20 && x < 10 && y < 25) {
			button_state = 2;
			reset_buttons();
			buttons[3].setState(1);
			SoundEngineTD->play2D("select.mp3", false);
		}
		if (x >= 10 && y >= 15 && x < 15 && y < 20) {
			button_state = 3;
			reset_buttons();
			buttons[4].setState(1);
			SoundEngineTD->play2D("select.mp3", false);
		}
		if (x >= 10 && y >= 20 && x < 15 && y < 25) {
			button_state = 4;
			reset_buttons();
			buttons[5].setState(1);
			SoundEngineTD->play2D("select.mp3", false);
		}
	}
	return 0;
}

// updates the game state of tower defense for every iteration
int TowerDefense::update(int fps)
{
	switch (state) {
	case 0:
		init_level();
		++level;
		++state;
		//m.init_map(2);
		break;
	case 1:
		//m.init_map(2);
		map_towers();
		advance_enemies(fps);
		if (state == 1){ advance_projectiles(fps); }
		if (enemies.size() == 0) { 
			clear_Projectiles();
			state = 2;
			buttons[0].setState(3);
			if (through > 0) { return 1; }
		}

		break;
	case 2:
		if (through) { return 1; }
		if (print == 0) {
			/*std::cout << "\n\n\n\t end level \n\t money: " << get_money() <<
				"\n\t " << thru() << " enemies got through" << "\n\t Lives:" << get_lives();*/
			print = 30;
		}
		else { ++print;}
		break;
	case 3:
		if (print == 0) {
			//std::cout << "Money: " << get_money() << "\t\t got thru: " << thru() << "\t\t lives: " << get_lives() << std::endl;
			print = 30;
		}
		else { ++print; }
		break;
	}
	if (through && state == 2) { return 1; }
	return 0;
}

void TowerDefense::render()
{
	m_pGraphics->drawMap();

	std::vector<unsigned int> vciIndices = { 0, 1, 2, 0, 2, 3 };
	std::vector<float> vcfSquare = {
		0.5, -0.5,
		0.5, -4.5,
		4.5, -4.5,
		4.5, -0.5
	};
	std::vector<float> vcfDiamond = {
		2.5, -0.0,
		5.0, -2.5,
		2.5, -5.0,
		0.0, -2.5
	};

	Model * pSquare = new Model(vcfSquare, vciIndices);
	Model * pDiamond = new Model(vcfDiamond, vciIndices);
	int iIndex = 0;
	
	for (float xShift = 0; xShift < 24; xShift += 5)
	{
		for (float yShift = 15; yShift < 24; yShift += 5)
		{
			m_pGraphics->drawModel(pSquare, 1.0f, 0.0f, xShift, yShift, 0.5f, 0.5f, 0.5f);

			switch (buttons[iIndex].getState())
			{
			case 0:
				m_pGraphics->drawModel(pDiamond, 1.0f, 0.0f, xShift, yShift, 0.5f, 0.5f, 0.5f);
				break;
			case 1:
				m_pGraphics->drawModel(pDiamond, 1.0f, 0.0f, xShift, yShift, 1.0f, 0.0f, 1.0f);
				break;
			case 3:
				m_pGraphics->drawModel(pDiamond, 1.0f, 0.0f, xShift, yShift, 0.0f, 1.0f, 0.0f);
				break;
			case 4:
				m_pGraphics->drawModel(pDiamond, 1.0f, 0.0f, xShift, yShift, 1.0f, 0.0f, 0.0f);
				break;
			default:
				m_pGraphics->drawModel(pDiamond, 1.0f, 0.0f, xShift, yShift, 0.5f, 0.5f, 0.5f);
			}
			iIndex++;
		}
	}

	for (Enemy enemy : enemies)
	{
		enemy.render(m_pGraphics);
	}

	for (Tower tower : towers)
	{
		tower.render(m_pGraphics);
	}

	m_pGraphics->drawText("Money", *m_pFont, 15.5, 16.5, 4, 2, 0, 1, 0, 1);
	m_pGraphics->drawText(std::to_string(money), *m_pFont, 15.5, 18.5, 4, 2, 0, 1, 0, 1);

	m_pGraphics->drawText("Level", *m_pFont, 15.5, 21.5, 4, 2, 0, 1, 0, 1);
	m_pGraphics->drawText(std::to_string(level), *m_pFont, 16.5, 23.5, 2, 2, 0, 1, 0, 1);

	m_pGraphics->drawText("Basic", *m_pFont, 5.5, 17.5, 4, 2, 0, 0, 0, 1);
	m_pGraphics->drawText("Ranged", *m_pFont, 5.5, 22.5, 4, 2, 0, 0, 0, 1);
	m_pGraphics->drawText("Machine", *m_pFont, 10.5, 17.5, 4, 2, 0, 0, 0, 1);
	m_pGraphics->drawText("Slow", *m_pFont, 10.5, 22.5, 4, 2, 0, 0, 0, 1);


}


void TowerDefense::init_level()
{
	switch (level) {
	case 0:
		make_wave(0, 10, normal, 10);
		break;
	case 1:
		make_wave(0, 10, normal, 10);
		make_wave(100, 20, strong, 4);
		break;
	case 2:
		make_wave(0, 10, normal, 10);
		make_wave(100, 20, fast, 5);
		break;
	case 3:
		make_wave(0, 10, normal, 10);
		make_wave(100, 20, tank, 5);
		break;
	case 4:
		make_wave(0, 10, normal, 10);
		make_wave(110, 20, miniboss, 1);
		break;
	case 5:
		make_wave(0, 5, strong, 10);
		make_wave(50, 20, tank, 10);
		make_wave(0, 25, fast, 10);
		break;
	case 6:
		make_wave(0, 3, normal, 20);
		make_wave(60, 5, strong, 15);
		make_wave(100, 10, tank, 10);
		break;
	case 7:
		make_wave(0, 7, tank, 12);
		make_wave(0, 13, strong, 12);
		make_wave(150, 10, fast, 40);
		break;
	case 8:
		make_wave(0, 5, strong, 25);
		make_wave(125, 3, tank, 40);
		break;
	case 9:
		make_wave(0, 3, fast, 50);
		make_wave(110, 10, boss, 1);
		break;
	case 10:
		make_wave(0, 10, miniboss, 10);
		make_wave(0, 5, fast, 20);
		break;
	case 11:
		make_wave(0, 5, tank, 20);
		make_wave(0, 3, fast, 40);
		make_wave(0, 10, miniboss, 15);
		break;
	case 12:
		make_wave(0, 10, boss, 10);
		break;
	case 13:
		make_wave(0, 5, fastmini, 20);
		make_wave(100, 5, boss, 5);
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
				/*std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t end level \n\t money: " << get_money() <<
					"\n\t " << thru() << " enemies got through \n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";*/
				clear_Projectiles();
				state = 2;
				buttons[0].setState(3);
				
			}
		
		}
		else {
			for (int t = 0; t < towers.size(); ++t) {
				towers[t].detect(enemies[j].get_xPos(), enemies[j].get_yPos());
			}
			
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
		while (c >= 1 && towers[t].get_projectiles_size()) {
			if (!towers[t].advanceProjectiles((c - 1), fps)) {

				//towers[t].eraseProjectile(c - 1);
				//--c;
				//if (towers[t].get_pnumber()) { --c; }
				
				
					double x = towers[t].get_projectile_x(c - 1);
					double y = towers[t].get_projectile_y(c - 1);
				
				
					//m.set_map_value((int)x, (int)y, '.');
					if (!enemies.size()) {
						state = 2;

					}
					for (unsigned int j = 0; j < enemies.size(); ++j) {
						if (enemies[j].detect(x, y)) {
							enemies[j].hit_response(towers[t].get_strength());
							if (c >= 1) {
								towers[t].eraseProjectile(c - 1);
							}
						}
						if (enemies[j].get_hp() <= 0) {
							add_money(enemies[j].get_reward());
							enemies.erase(enemies.begin() + j);
							SoundEngineTD->play2D("Sounds/die.mp3", false);
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

int TowerDefense::thru() 
{
	int t = through;
	through = 0;
	return t;
}

int TowerDefense::get_thru()
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

void TowerDefense::create_button(int x, int y, int s)
{
	Button *b = new Button(x, y, s);
	buttons.push_back(*b);
}

void TowerDefense::reset_buttons()
{
	for (int j = 2; j < buttons.size(); ++j) {
		buttons[j].setState(0);
	}
}


int TowerDefense::get_map_value(int x, int y)
{
	if (x > -1 && x<25 && y>-1 && y < 15) {
		return m.get_map_value(x, y);
	}
	return -1;
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

void TowerDefense::reset_through()
{
	through = 0;
}


