#include "Tower.h"
#include<cmath>
#include<iostream>
#include<Sound/irrKlang.h>

irrklang::ISoundEngine *SoundEngineTower = irrklang::createIrrKlangDevice();

Tower::Tower(int x, int y, int s)
{
	xPos = x;
	yPos = y;
	strength = s;
	timer = 0;
	pnumber = 0;
	switch (s)
	{
		case basic:
			cooldown = 50;
			range = 5;
			speed = 20;
			break;
		case ranged:
			cooldown = 75;
			range = 15;
			speed = 40;
			break;
		case machine:
			cooldown = 12;
			range = 5;
			speed = 20;
			break;
		case slow_t:
			cooldown = 50;
			range = 5;
			speed = 20;
			break;
	}
	/*if (strength == basic) {
		cooldown = 20;
		range = 5;
		speed = 1;
	}
	if (strength == ranged) {
		cooldown = 30;
		range = 10;
		speed = 1;
	}
	if (strength == machine) {
		cooldown = 2;
		range = 5;
		speed = 2;
	}
	*/
}

void Tower::render(Graphics* pGraphics)
{
	switch (strength)
	{
	case basic:
		pGraphics->drawRegularPolygon(20, 0.3, 0.0, xPos, yPos, 0.0, 1.0, 0.0);
		break;
	case ranged:
		pGraphics->drawRegularPolygon(3, 0.3, 0.0, xPos, yPos, .15, 0.976, 0.8);
		break;
	case machine:
		pGraphics->drawRegularPolygon(4, 0.3, 0.0, xPos, yPos, .619, .35, 0.976);
		break;
	case slow_t:
		pGraphics->drawRegularPolygon(5, 0.3, 90.0, xPos, yPos, 1, 1, 0.0);
		break;
	}

	for (Projectile projectile : projectiles)
	{
		projectile.render(pGraphics);
	}
}


void Tower::detect(double x, double y)
{
	if (timer == 0) {
		double xdist = xPos - x;
		double ydist = yPos - y;
		double dist = sqrt(xdist*xdist + ydist * ydist);
		if (dist < range && x != 0) {
			pnumber += 1;
			double xV = -1 * xdist * speed / dist;
			double yV = -1 * ydist * speed / dist;
			Projectile *p1 = new Projectile(xPos, yPos, xV, yV, strength);
			projectiles.push_back(*p1);
			timer += cooldown;

			// play different sounds for different towers
			switch (strength)
			{
			case(basic):
				SoundEngineTower->play2D("pew.mp3", false); 
				break;
			case(ranged):
				SoundEngineTower->play2D("Sounds/ranged_tower.mp3", false);
				break;
			case(machine):
				SoundEngineTower->play2D("pew.mp3", false);
				break;
			case(slow_t):
				SoundEngineTower->play2D("Sounds/slow.mp3", false);
				break;
			}
	
			//std::cout << "SHOT";

		
		}
	}
}

int Tower::advanceProjectiles(int pnum, int fps)
{
	int p = 0;
	if (projectiles.size()>pnum) { p = projectiles[pnum].advance(fps); }
	
	if (p) { --pnumber; }
	
	return p;
}

void Tower::cool()
{
	pnumber = projectiles.size();
	if (timer > 0) {
		--timer;
	}
	if (pnumber < 0) {
		pnumber = 0;
	}
}

void Tower::eraseProjectile(int pnum)
{
	
	if (pnumber > 0) {
		--pnumber;
		if (!((pnumber+1) == pnum && pnum == projectiles.size())) { projectiles.erase(projectiles.begin() + pnum); }
	}
	
	
}

double Tower::get_pnumber() {
	return pnumber;

}

double Tower::get_projectile_x(int pnum)
{

	return projectiles[pnum].get_xPos();
	
}

double Tower::get_projectile_y(int pnum)
{
	return projectiles[pnum].get_yPos();
}

void Tower::clear_p()
{
	pnumber = 0;
	for (int j = 0; j < projectiles.size(); ++j) {
		projectiles.erase(projectiles.begin() + j);
	}
	
}

int Tower::get_strength() const
{
	return strength;
}

double Tower::get_xPos() const
{
	return xPos;
}

double Tower::get_yPos() const
{
	return yPos;
}

int Tower::get_projectiles_size()
{
	return projectiles.size();
}
