#include "StdAfx.h"
#include "BoxPH.h"


BoxPH::BoxPH(void)
{
}

BoxPH::BoxPH(const Box &bx)
	: Box(bx), PhysicsObject(Vector(), bx.volume(), 0)
{

}

BoxPH::BoxPH(const Box &bx, const Vector &_vel)
	: Box(bx), PhysicsObject(_vel, bx.volume(), 0)
{
}

BoxPH::BoxPH(const Box &bx, const Vector &_vel, double _mass, bool _frozen)
	: Box(bx), PhysicsObject(_vel, _mass, _frozen)
{
}

BoxPH::~BoxPH(void)
{
}

Vector BoxPH::getPos() const
{
	return a;
}

void BoxPH::setPos(const Vector &_v)
{
	a = _v;
}

void BoxPH::update(double dt)
{
	if(!frozen)
	{
		if(flr)
		{
			double fr = 50. * dt;
			if(fr * fr <= vel.length2() && vel.length2() > EPS)
				vel -= vel.normalized() * fr;
			else
				vel = Vector();
		}
		else
			vel += gravity * dt;
		a += vel * dt;
	}
}