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

void Bolt::render(Graphics* pGraphics)
{
	pGraphics->drawRegularPolygon(30, 0.3f, 0.0f, xPos, yPos, 1.0f, 0.0f, 1.0f);
}


int Bolt::check_hit(double x, double y) {
	if (abs(xPos - x) < hitbox_d && abs(yPos - y) < hitbox_d) {
		return 1;
	}
	return 0;
}
