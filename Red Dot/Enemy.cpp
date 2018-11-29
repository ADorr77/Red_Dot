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
		reward = 100;
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

	/*
	if ((int)xPos == 4 && (int)yPos == 11) {
		xVel = 0;
		yVel = -speed;
	}
	if ((int)xPos == 4 && (int)yPos == 7) {
		xVel = -speed;
		yVel = 0;
	}
	if ((int)xPos == 2 && (int)yPos == 7) {
		xVel = 0;
		yVel = -speed;
	}
	if ((int)xPos == 2 && (int)yPos == 2) {
		xVel = speed;
		yVel = 0;
	}
	if ((int)xPos == 17 && (int)yPos == 2) {
		xVel = 0;
		yVel = speed;
	}
	if ((int)xPos == 17 && (int)yPos == 13) {
		xVel = -speed;
		yVel = 0;
	}
	if ((int)xPos == 13 && (int)yPos == 13) {
		xVel = 0;
		yVel = -speed;
	}
	if ((int)xPos == 13 && (int)yPos == 6) {
		xVel = -speed;
		yVel = 0;
	}
	if ((int)xPos == 9 && (int)yPos == 6) {
		xVel = 0;
		yVel = speed;
	}*/
	xPos += xVel;
	yPos += yVel;
}

void Enemy::setTimer(int t) {
	timer = t;
}

int Enemy::detect(double x, double y)
{
	double xdist = xPos - x;
	double ydist = yPos - y;
	double dist = sqrt(xdist*xdist + ydist * ydist);
	if (dist < 1) {
		return 1;
	}
	return 0;
}

double Enemy::get_xPos() const
{
	return xPos;
}

double Enemy::get_yPos() const
{
	return yPos;
}

double Enemy::get_xVel() const
{
	return xVel;
}

double Enemy::get_yVel() const
{
	return yVel;
}

int Enemy::get_reward() const
{
	return reward;
}

void Enemy::set_xVel(int i)
{
	xVel = i * speed;
}

void Enemy::set_yVel(int i)
{
	yVel = i * speed;
}
