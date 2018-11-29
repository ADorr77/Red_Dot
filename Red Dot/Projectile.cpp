#include "Projectile.h"

void Projectile::advance()
{
	xPos += xVel;
	yPos += yVel;
}

void Projectile::setVals(double x, double y, double xV, double yV, int p)
{
	xPos = x;
	yPos = y;
	xVel = xV;
	yVel = yV;
	power = p;
}
