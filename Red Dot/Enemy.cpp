#include"Enemy.h"


Enemy::Enemy(int level) {
	yPos = 11;
	xPos = 0;
	if (level = 1) {
		speed = .25;
		hp = 1;
		strength = 1;
		xVel = 0;
		yVel = 0;
	}
}

void Enemy::advance() {
	//when timer hits zero, start sending enemy through path
	if (timer == 0){
		timer = -1;
		xVel = speed;
	}
	//decrease timer till it hits zero
	if (timer > 0) { --timer; }

	if ((int)xPos == 4 && (int)yPos == 11) {
		xVel = 0;
		yVel = -speed;
	}
	xPos += xVel;
	yPos += yVel;
}

void Enemy::setTimer(int t) {
	timer = t;
}

double Enemy::get_xPos() const
{
	return xPos;
}

double Enemy::get_yPos() const
{
	return yPos;
}

void Enemy::set_xVel(int i)
{
	xVel = i * speed;
}

void Enemy::set_yVel(int i)
{
	yVel = i * speed;
}
