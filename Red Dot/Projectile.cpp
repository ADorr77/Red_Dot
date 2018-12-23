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

int Projectile::advance(int fps)
{
	xPos += xVel/fps;
	yPos += yVel/fps;
	if (xPos > 24 || yPos > 15 || xPos < 0 || yPos < 0) {
		return 1;
	}
	else { return 0; }
	//return 0;
	
}

void Projectile::render(Graphics* pGraphics)
{
	pGraphics->drawRegularPolygon(30, 0.15f, 0.0f, xPos, yPos, 1.0f, 0.0f, 1.0f);
}


void Projectile::setVals(double x, double y, double xV, double yV, int p)
{
	xPos = x;
	yPos = y;
	xVel = xV;
	yVel = yV;
	power = p;
}

