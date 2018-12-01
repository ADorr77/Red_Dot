#include"Enemy.h"

enum {regen, normal, strong, fast, tank};
Enemy::Enemy(int level) {
	yPos = 11;
	xPos = 0;
	if (level == normal) {
		speed = .25;
		hp = 1;
		strength = 1;
		xVel = 0;
		yVel = 0;
		reward = 100;
	}
	if (level == strong) {
		speed = .25;
		hp = 2;
		strength = 1;
		xVel = 0;
		yVel = 0;
		reward = 150;
	}
	if (level == fast) {
		speed = .50;
		hp = 1;
		strength = 1;
		xVel = 0;
		yVel = 0;
		reward = 150;
	}
	if (level == tank) {
		speed = .125;
		hp = 1;
		strength = 4;
		xVel = 0;
		yVel = 0;
		reward = 200;
	}
}

int Enemy::advance() {
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
	if (yPos > 15 || xPos >20) {
		return 1;
	}
	else { return 0; }
}

void Enemy::setTimer(int t) {
	timer = t;
}

int Enemy::detect(double x, double y)
{
	double xdist = xPos - x;
	double ydist = yPos - y;
	double dist = sqrt(xdist*xdist + ydist * ydist);
	if (dist < .6) {
		return 1;
	}
	return 0;
}

void Enemy::take_damage(double x, double y)
{
	if (detect(x, y)) {
		hp -= 1;
	}
}

double Enemy::get_hp() const
{
	return hp;
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

void Enemy::update_velocities(Maps m)
{
	int f = m.get_map_value(xPos + 1, yPos);
	int b = m.get_map_value(xPos - 1, yPos);
	int u = m.get_map_value(xPos, yPos - 1);
	int d = m.get_map_value(xPos, yPos + 1);

	if (xVel > 0) {
		if (f == -37) {
			if (u != -37) {
				set_xVel(0);
				set_yVel(-1);
			}
			if (d != -37) {
				set_xVel(0);
				set_yVel(1);
			}
		}
	}
	else if (xVel < 0) {
		if (b == -37) {
			if (u != -37) {
				set_xVel(0);
				set_yVel(-1);
			}
			if (d != -37) {
				set_xVel(0);
				set_yVel(1);
			}
		}
	}
	else if (yVel < 0) {
		if (u == -37) {
			if (f != -37) {
				set_xVel(1);
				set_yVel(0);
			}
			if (b != -37) {
				set_xVel(-1);
				set_yVel(0);
			}
		}
	}
	else if (yVel > 0) {
		if (d == -37) {
			if (f != -37) {
				set_xVel(1);
				set_yVel(0);
			}
			if (b != -37) {
				set_xVel(-1);
				set_yVel(0);
			}
		}
	}
}
