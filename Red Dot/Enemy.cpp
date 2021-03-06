#include"Enemy.h"
#include"Tower.h"
Enemy::Enemy(int level) {
	yPos = 11;
	xPos = 0;
	slow_timer = 0;
	type = level;
	if (level == normal) {
		speed = 10;
		hp = 1;
		strength = 1;
		xVel = 0;
		yVel = 0;
		reward = 50;
		type_char = 'e';
	}
	if (level == strong) {
		speed = 10;
		hp = 3;
		strength = 1;
		xVel = 0;
		yVel = 0;
		reward = 100;
		type_char = 's';
	}
	if (level == fast) {
		speed = 15;
		hp = 1;
		strength = 1;
		xVel = 0;
		yVel = 0;
		reward = 50;
		type_char = 'f';
	}
	if (level == tank) {
		speed = 6;
		hp = 6;
		strength = 2;
		xVel = 0;
		yVel = 0;
		reward = 150;
		type_char = 'e';
	}
	if (level == miniboss) {
		speed = 5;
		hp = 50;
		strength = 25;
		xVel = 0;
		yVel = 0;
		reward = 500;
		type_char = 'b';
	}
	if (level == fastmini) {
		speed = 10;
		hp = 50;
		strength = 25;
		xVel = 0;
		yVel = 0;
		reward = 500;
		type_char = 'b';
	}
	if (level == boss) {
		speed = 5;
		hp = 200;
		strength = 50;
		xVel = 0;
		yVel = 0;
		reward = 1000;
		type_char = 'b';
	}
	if (level == fastboss) {
		speed = 10;
		hp = 200;
		strength = 50;
		xVel = 0;
		yVel = 0;
		reward = 1000;
		type_char = 'b';
	}
	if (level == megaboss) {
		speed = 5;
		hp = 1000;
		strength = 50;
		xVel = 0;
		yVel = 0;
		reward = 2000;
		type_char = 'b';
	}
}

int Enemy::advance(int fps) {
	//when timer hits zero, start sending enemy through path
	if (timer == 0){
		timer = -1;
		xVel = speed;
	}
	//decrease timer till it hits zero
	if (timer > 0) { --timer; }
	xPos += xVel/fps;
	yPos += yVel/fps;
	if (yPos > 15 || xPos >24.5) {
		return 1;
	}
	else { return 0; }

	// delete this jawn
	//if (slow_timer > 0) { --slow_timer; } // count down the slow timer if enemy is being slowed.
	//if (slow_timer = 1) // resets velocities once slow_timer is down.
	//{
		//speed *= 4;
	//}
}

void Enemy::render(Graphics* pGraphics)
{
	switch(type)
	{
	case normal:
		pGraphics->drawRegularPolygon(30, 0.3, 0.0f, xPos, yPos, 1.0);
		break;
	case strong:
		pGraphics->drawRegularPolygon(30, 0.3, 0.0f, xPos, yPos, 1.0, 0.557, 0.91);
		break;
	case fast:
		pGraphics->drawRegularPolygon(4, 0.3, 0.0f, xPos, yPos, 0.0, 1.0, 0.0);
		break;
	case tank:
		pGraphics->drawRegularPolygon(30, 0.3, 0.0f, xPos, yPos, 1.0, 1.0, 1.0);
		break;
	case boss:
		pGraphics->drawRegularPolygon(30, 0.4, 0.0f, xPos, yPos, 1.0, 0.0, 0.0);
		break;
	case miniboss:
		pGraphics->drawRegularPolygon(30, 0.4, 0.0f, xPos, yPos, .188, 0.863, 0.5);
		break;
	case fastmini:
		pGraphics->drawRegularPolygon(4, 0.4, 0.0f, xPos, yPos, 0, 0.9, 0);
		break;
	case fastboss:
		pGraphics->drawRegularPolygon(4, 0.4, 0.0f, xPos, yPos, .188, 0.863, 1.0);
		break;
	case megaboss:
		pGraphics->drawRegularPolygon(30, 0.4, 0.0f, xPos, yPos, 0, 0, 0);
		break;
	}
}


void Enemy::setTimer(int t) {
	timer = t;
}

int Enemy::detect(double x, double y)
{
	if (xPos == 0) { return 0; }
	double xdist = xPos - x;
	double ydist = yPos - y;
	double dist = sqrt(xdist*xdist + ydist * ydist);
	if (dist < 1) {
		return 1;
	}
	return 0;
}

void Enemy::take_damage(int type)
{
	// damage settings
	switch (type)
	{

	case (basic):
		hp -= 1;
		break;
	case (ranged):
		hp -= 2;
		break;
	case (machine):
		hp -= 1;
		break;
	}

}

void Enemy::slow()
{
	if (slow_timer == 0) // prevents slow effect from accumulating 
	{
		slow_timer = 30; //temporary large timer to see effect 
		speed *= .25;
	}
}

void Enemy::hit_response(int type)
{
	switch (type) {
	case (basic):
		take_damage(type);
		break;
	case (ranged):
		take_damage(type);
		break;
	case (machine):
		take_damage(type);
		break;
	case (slow_t):
		slow();
		break;
	}
}

double Enemy::get_strength() const
{
	return strength;
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
	int f = m.get_map_value((xPos) + 1, (yPos));
	int b = m.get_map_value((xPos) - 1, (yPos));
	int u = m.get_map_value((xPos), (yPos) - 1);
	int newu = m.get_map_value((xPos), (yPos-.2));
	int newb = m.get_map_value((xPos - .2), (yPos));
	int d = m.get_map_value((xPos), (yPos) + 1);

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
		if (newb == -37) {
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
		if (newu == -37) {
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
