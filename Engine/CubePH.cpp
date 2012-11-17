#include "StdAfx.h"
#include "CubePH.h"


CubePH::CubePH(void)
{
}

CubePH::CubePH(const Cube &cb)
	: Cube(cb), PhysicsObject(Vector(), cb.volume(), 0)
{
}

CubePH::CubePH(const Cube &cb, const Vector &_vel)
	: Cube(cb), PhysicsObject(_vel, cb.volume(), 0)
{
}

CubePH::CubePH(const Cube &cb, const Vector &_vel, double _mass, bool _frozen)
	: Cube(cb), PhysicsObject(_vel, _mass, _frozen)
{
}

CubePH::~CubePH(void)
{
}

Vector CubePH::pos()
{
	return a;
}

void CubePH::update(double dt)
{
	if(!frozen)
	{
		a += (vel + gravity * dt) / 2. * dt;
		vel += gravity * dt;
	}
}