#include"Bolt.h"
#include<cmath>
#include"Dungeon.h"

Bolt::Bolt(double d, double V, double xV, double yV, double xP, double yP){
	xPos = xP;
	yPos = yP;
	xVel = xV;
	yVel = yV;
	damage = d;
	hitbox_d = 0.5;
}

void Bolt::move()
{
	xPos += xVel;
	yPos += yVel;
}

int Bolt::check_hit(double x, double y) {
	if (abs(xPos - x) < hitbox_d && abs(yPos - y) < hitbox_d) {
		return 1;
	}
	return 0;
}
