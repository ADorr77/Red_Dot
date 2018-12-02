#include"Enemy.h"
#include"Tower.h"
Enemy::Enemy(int level) {
	yPos = 11;
	xPos = 0;
	slow_timer = 0;
	type = level;
	if (level == normal) {
		speed = .25;
		hp = 1;
		strength = 1;
		xVel = 0;
		yVel = 0;
		reward = 100;
		type_char = 'e';
	}
	if (level == strong) {
		speed = .25;
		hp = 2;
		strength = 1;
		xVel = 0;
		yVel = 0;
		reward = 150;
		type_char = 's';
	}
	if (level == fast) {
		speed = .50;
		hp = 1;
		strength = 1;
		xVel = 0;
		yVel = 0;
		reward = 150;
		type_char = 'f';
	}
	if (level == tank) {
		speed = .125;
		hp = 4;
		strength = 2;
		xVel = 0;
		yVel = 0;
		reward = 200;
		type_char = 'e';
	}
	if (level == boss) {
		speed = .125;
		hp = 50;
		strength = 50;
		xVel = 0;
		yVel = 0;
		reward = 200;
		type_char = 'b';
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
	xPos += xVel;
	yPos += yVel;
	if (yPos > 15 || xPos >24.5) {
		return 1;
	}
	else { return 0; }

	if (slow_timer > 0) { --slow_timer; } // count down the slow timer if enemy is being slowed.
	if (slow_timer = 1) // resets velocities once slow_timer is down.
	{
		xVel *= 2;
		yVel *= 2;
	}
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

void Enemy::take_damage()
{
		hp -= 1;
}

void Enemy::slow()
{
	slow_timer = 1000; //temporary large timer to see effect 
	xVel *= 0.25;
	yVel *= 0.25;
}

void Enemy::hit_response(int type)
{
	switch (type) {
	case (basic):
		take_damage();
		break;
	case (ranged):
		take_damage();
		break;
	case (machine):
		take_damage();
		break;
	case (slow_t):
		slow();
		break;
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
