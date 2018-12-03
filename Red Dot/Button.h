#pragma once
#ifndef BUTTON_H
#define BUTTON_H

class Button
{
private:
	int xPos, yPos;
	int state = 0;

public:
	Button(int x, int y, int s);
	void getPos(int &x, int &y);
	int get_x_Pos() const;
	int get_y_Pos() const;
	void setPos(int x, int y);
	int getState() const;
	void setState(int s);
};


#endif