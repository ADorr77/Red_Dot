#include "Button.h"

Button::Button(int x, int y, int s)
{
	xPos = x;
	yPos = y;
	state = s;
}

void Button::getPos(int & x, int & y)
{
	x = xPos;
	y = yPos;
}

int Button::get_x_Pos() const
{
	return xPos;
}

int Button::get_y_Pos() const
{
	return yPos;
}

void Button::setPos(int x, int y)
{
	xPos = x;
	yPos = y;
}

int Button::getState() const
{
	return state;
}

void Button::setState(int s)
{
	state = s;
}
