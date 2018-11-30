#include "Projectile.h"

Projectile::Projectile(int p)
{
	xPos = 0;
}

Projectile::Projectile(double x, double y, double xV, double yV, int p)
{
	xPos = x;
	yPos = y;
	xVel = xV;
	yVel = yV;
	power = p;
}

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

