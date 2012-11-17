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
		dir.z * sin(phiy),
		dir.z * cos(phiy)
		);
	v = Vector
		(
		v.x * cos(phix) - v.z * sin(phix),
		v.y,
		v.x * sin(phix) + v.z * cos(phix)
		);
	v = (v + Vector(0, dir.y, 0)).normalized() * 7.;
	p += v * t;

}

Vector Player::pos()
{
	throw std::exception("The method or operation is not implemented.");
}

Vector Player::getPos() const
{
	return p;
}

void Player::setPos(const Vector &_v)
{
	p = _v;
}