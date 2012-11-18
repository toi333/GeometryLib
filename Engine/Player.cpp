#include "StdAfx.h"
#include "Player.h"


Player::Player(void)
{
	vel = Vector();
	d = 1.;
	mass = 1.;
}

Player::Player(double _d)
	: d(_d)
{
	vel = Vector();
	mass = 1.;
}

Player::~Player(void)
{
}

void Player::update(double t)
{
	double phix = yaw * M_PI / 180.;
	double phiy = pitch * M_PI / 180.;
	Vector v
		(
		dir.x,
		0,
		dir.z
		);
	v = Vector
		(
		v.x * cos(phix) - v.z * sin(phix),
		v.y,
		v.x * sin(phix) + v.z * cos(phix)
		);
	if(flr)
		vel += v.normalized() * 200. * t;
	else
		vel += v.normalized() * 10. * t;
	p += vel * t;
	vel += gravity * t;
	//printf("%d\n", flr != 0);
	transform();
}

Vector Player::getPos() const
{
	return p;
}

void Player::setPos(const Vector &_v)
{
	p = _v;
}