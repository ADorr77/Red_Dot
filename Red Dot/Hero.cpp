
#include"Hero.h"
#include<cmath>
#include"Dungeon.h"

Hero::Hero()
{
	maxHealth = 100;
	health = maxHealth;
	level = 1;
	exp = 0;
	xPos = 6;
	yPos = 14;
	Vel = 5;
	weapon = 0;
	damage = 2;
	m_dMeleRange = 1.5;
	m_dMeleAngle = 3.14159265 / 6;
	m_dHeroRadius = 0.3;

	std::vector<float> vcfPoints = {
		m_dHeroRadius,							0.0f,
		(m_dMeleRange * cos(m_dMeleAngle)),		(m_dMeleRange * sin(m_dMeleAngle)),
		(m_dMeleRange),							0.0f,
		(m_dMeleRange * cos(m_dMeleAngle)),		0.0f - (m_dMeleRange * sin(m_dMeleAngle))
	};
	std::vector<unsigned int> vciIndices = { 0, 1, 2, 0, 2, 3 };
	m_pSwordSwing = new Model(vcfPoints, vciIndices);
}

Hero::Hero(double level, int mapSize) {
	maxHealth = 100 + (10 * level);
	health = maxHealth;
	this->level = level;
	exp = 0;
	xPos = mapSize/2;
	yPos = mapSize/2;
	Vel = 0.3;
	weapon = 0;
	damage = 2 + (level * 0.1);

	m_dMeleRange = 1.5;
	m_dMeleAngle = 3.14159265 / 6;
	m_dHeroRadius = 0.3;

	std::vector<float> vcfPoints = {
		m_dHeroRadius,							0.0f,
		(m_dMeleRange * cos(m_dMeleAngle)),		(m_dMeleRange * sin(m_dMeleAngle)),
		(m_dMeleRange),							0.0f,
		(m_dMeleRange * cos(m_dMeleAngle)),		0.0f - (m_dMeleRange * sin(m_dMeleAngle))
	};
	std::vector<unsigned int> vciIndices = { 0, 1, 2, 0, 2, 3 };
	m_pSwordSwing = new Model(vcfPoints, vciIndices);
}

void Hero::update() {
}

void Hero::render(Graphics * pGraphics)
{
	pGraphics->drawRegularPolygon(30, m_dHeroRadius, 0.0f, xPos, yPos, 0.0f, 1.0f, 0.0f);
	pGraphics->drawLoadingBar(xPos, yPos - 0.2, 1.0f, 0.15f, health / maxHealth);
}

void Hero::renderAttack(Graphics* pGraphics)
{
	double dAngle = (atan(yDir / xDir) * 180.0) / 3.14159265;
	if (xDir < 0)
		dAngle += 180.0;
	pGraphics->drawModel(m_pSwordSwing, 1.0, dAngle, xPos + 0.5f, yPos + 0.5f, 1.0f, 1.0f, 1.0f);
}

void Hero::move(int x, int y) {
	// x and y are just trackers to check "wasd" moves 
	if (x && y) {
		xPos += (x) * (Vel) / (sqrt(2));
		yPos += (y) * (Vel) / (sqrt(2));
	}
	else {
		xPos += Vel * x;
		yPos += Vel * y;
	}
}

void Hero::set_direction(double x, double y) {
	// takes in cursor coordinates
	double distance = sqrt(pow(x-xPos,2) + pow(y-yPos,2));
	xDir = (x - xPos) / distance;
	yDir = (y - yPos) / distance;
}

double Hero::melee_attack(double x, double y) {
	// Distance to monster
	double distM = sqrt(pow(x - xPos, 2) + pow(y - yPos, 2));
	if (distM <= m_dMeleRange) {
		double angle_M = atan((y - yPos) / (x - xPos));	// Monster angle
		double angle_C = atan(yDir / xDir);	// Cursor angle
		if (angle_C - (m_dMeleAngle) < angle_M && angle_C + (m_dMeleAngle) > angle_M) {
			return 5;
		}
	}
	return 0;
}

Bolt Hero::ranged_attack() {
	return Bolt::Bolt((damage), 0.01, (xDir), (yDir), xPos, yPos);
}

void Hero::switch_Weapon() {
	this->weapon = (weapon == 1 ? 0 : 1);
}

void Hero::take_damage(double attack) {
	health -= attack;
}

void Hero::add_exp(double xp) {
	exp += xp;
}

void Hero::level_up() {
	if (exp > (50 * (level - 0.5))) {
		maxHealth = 100 + (10 * level);
		health = maxHealth;
		level++;
	}
}

int Hero::die() {
	if (health < 0) {
		return 1;
	}
	return 0;
}

