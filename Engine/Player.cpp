#include "StdAfx.h"
#include "Player.h"

Vector Player::d = Vector(0.794016819, 1.8, 0.794016819);//1.21^-1.21
double Player::pmass = 1.21;

Player::Player(void)
{
	mass = pmass;
	vel = Vector();
	p = Vector(0, 30, 0);
}

Player::~Player(void)
{
}

void Player::jump()
{
	if(flr)
	{
		vel.y += 17.;
		flr = 0;
	}
}


void Player::update(double dt)
{
	Vector a;
	double phix = cam.yaw * M_PI / 180.;
	double phiy = cam.pitch * M_PI / 180.;
	if(gravity != Vector())
	{
		a = Vector
		(
			dir.x * cos(phix) - dir.z * sin(phix),
			0,
			dir.x * sin(phix) + dir.z * cos(phix)
		);
		a.normalize();
	}
	else
	{
		a = Vector
		(
			dir.x,
			dir.z * sin(phiy),
			dir.z * cos(phiy)
		);
		a = Vector
		(
			a.x * cos(phix) - a.z * sin(phix),
			a.y,
			a.x * sin(phix) + a.z * cos(phix)
		);
		a.y += dir.y;
		a.normalize();
	}

	if(gravity != Vector())
	{
		if(flr)
		{
			if(vel.length2() < 100.)
			{
				vel += a * 140 * dt;
				if(vel.length2() > 100.)
				{
					vel.normalize();
					vel *= 10.;
				}
			}
			double fr = 100. * dt;
			if(fr * fr <= vel.length2())
				vel -= vel.normalized() * fr;
			else
				vel = Vector();
		}
		else
		{
			vel += a * 2. * dt;
			vel += gravity * dt;
		}
	}
	else
		vel = a * 1210. * dt;

	p += vel * dt;
	cam.p = p;
	cam.p.y += 1.6;
}

Vector Player::getPos() const
{
	return p;
}

void Player::setPos(const Vector &_v)
{
	p = _v;
}

Box Player::getAABB()
{
	return Box(p, d);
}

void Player::move(const Vector &_dir)
{
	dir += _dir;
}