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

//bool CubePH::collide(const PhysicsObject *p, Vector &n) const
//{
//	if(p->phtype() == CUBEPH)
//		return collide((CubePH*)p, n);
//}
//
//bool CubePH::collide(const CubePH *p, Vector &n) const
//{
//	
//}