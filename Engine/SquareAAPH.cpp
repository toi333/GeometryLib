#include "StdAfx.h"
#include "SquareAAPH.h"


SquareAAPH::SquareAAPH(void)
{
}

SquareAAPH::SquareAAPH(const SquareAA &sq)
	: SquareAA(sq)
{
}

SquareAAPH::SquareAAPH(const SquareAA &sq, const Vector &_vel)
	: SquareAA(sq), PhysicsObject(_vel, sq.d * sq.d * 0.1, 0)
{
}

SquareAAPH::SquareAAPH(const SquareAA &sq, const Vector &_vel, double _mass, bool _frozen)
	: SquareAA(sq), PhysicsObject(_vel, _mass, _frozen)
{
}

SquareAAPH::~SquareAAPH(void)
{
}

Vector SquareAAPH::getPos() const
{
	return a;
}

void SquareAAPH::setPos(const Vector &_v)
{
	a = _v;
}

void SquareAAPH::update(double dt)
{
	if(!frozen)
		a += vel * dt;
}
