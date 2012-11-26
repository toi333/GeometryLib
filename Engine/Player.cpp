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

void Player::jump()
{
	if(flr)
	{
		vel.y += 10.;
		flr = 0;
	}
}


void Player::update(double dt)
{
	Vector v;
	double phix = yaw * M_PI / 180.;
	double phiy = pitch * M_PI / 180.;
	if(!(gravity == Vector()))
	{
		v = Vector
		(
			dir.x * cos(phix) - dir.z * sin(phix),
			0,
			dir.x * sin(phix) + dir.z * cos(phix)
		);
		v.normalize();
	}
	else
	{
		v = Vector
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
		v.y += dir.y;
		v.normalize();
	}

	if(flr)
	{
		if(vel.length2() < 100.)
		{
			vel += v * 140 * dt;
			if(vel.length2() > 100.)
			{
				vel.normalize();
				vel *= 10.;
			}
		}
		double fr = 100. * dt;
		if(fr * fr <= vel.length2() && vel.length2() > EPS)
			vel -= vel.normalized() * fr;
		else
			vel = Vector();
	}
	else
	{
		vel += v * 10. * dt;
		vel += gravity * dt;
	}

	p += vel * dt;
}

Vector Player::getPos() const
{
	return p;
}

void Player::setPos(const Vector &_v)
{
	p = _v;
}