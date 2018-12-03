#pragma once
#ifndef BUTTON_H
#define BUTTON_H

class Button
{
private:
	int xPos, yPos;
	int state = 0;
	// int type; Possible way to implement multiple types of enemies with enum
	// double speed; could have this too potentially
public:
	// Enemy constructor (pass in whatever you decide)
	Enemy();
	Enemy(int level);
	// update method to move it
	void update();
	// advance position
	int advance(int fps);


#endif