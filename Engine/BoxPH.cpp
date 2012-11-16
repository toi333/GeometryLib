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

Vector BoxPH::pos()
{
	return a;
}

void BoxPH::update(double dt)
{
	if(!frozen)
		a += vel * dt;
}

//bool BoxPH::collide(const PhysicsObject *p, Vector &n) const
//{
//	if(p->phtype() == BoxPH)
//		return collide((BoxPH*)p, n);
//}
//
//bool BoxPH::collide(const BoxPH *p, Vector &n) const
//{
//	
//}