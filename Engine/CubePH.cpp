#include "StdAfx.h"
#include "CubePH.h"


CubePH::CubePH(void)
{
}

CubePH::CubePH(Cube cb, Vector _vel) :
	Cube(cb), PhysicsObject(_vel)
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
	a += vel * dt;
}
