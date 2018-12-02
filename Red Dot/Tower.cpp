#include "Tower.h"
#include<cmath>
#include<iostream>


Tower::Tower(int x, int y, int s)
{
	xPos = x;
	yPos = y;
	strength = s;
	timer = 0;
	pnumber = 0;
	if (strength == basic) {
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
			std::cout << "SHOT";

		
		}
	}
}

int Tower::advanceProjectiles(int pnum)
{
	int p = projectiles[pnum].advance(); 
	if (p) { --pnumber; }
	
	return p;
}

void Tower::cool()
{
	if (timer > 0) {
		--timer;
	}
	if (pnumber < 0) {
		pnumber = 0;
	}
}

void Tower::eraseProjectile(int pnum)
{
	--pnumber;
	projectiles.erase(projectiles.begin() + pnum);
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

double Tower::get_strength() const
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
