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
	if (strength == 1) {
		cooldown = 20;
		range = 5;
		speed = 1;
	}
}

void Tower::detect(double x, double y)
{
	if (timer == 0) {
		double xdist = xPos - x;
		double ydist = yPos - y;
		double dist = sqrt(xdist*xdist + ydist * ydist);
		if (dist < range) {
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

void Tower::advanceProjectiles(int pnum)
{
	projectiles[pnum].advance();
}

void Tower::cool()
{
	if (timer > 0) {
		--timer;
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
