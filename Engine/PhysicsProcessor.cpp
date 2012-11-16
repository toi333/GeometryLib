#include "StdAfx.h"
#include "PhysicsProcessor.h"

using namespace std;

PhysicsProcessor::PhysicsProcessor(void)
{
}

PhysicsProcessor::~PhysicsProcessor(void)
{
}

void PhysicsProcessor::collide(CubePH &a, CubePH &b)
{
	if(a.frozen && b.frozen)
		return;

	double dx = intervalIntersection(a.a.x - a.d, a.a.x + a.d, b.a.x - b.d, b.a.x + b.d);
	if(dx <= EPS)
		return;
	int n = 0;
	double dy = intervalIntersection(a.a.y - a.d, a.a.y + a.d, b.a.y - b.d, b.a.y + b.d);
	if(dy <= EPS)
		return;
	if(dy < dx)
		n = 1;
	double dz = intervalIntersection(a.a.z - a.d, a.a.z + a.d, b.a.z - b.d, b.a.z + b.d);
	if(dz <= EPS)
		return;
	if(dz < dx && dz < dy)
		n = 2;

	double *av = 0, *bv = 0;
	if(!n)
	{
		if(sgn(a.vel.x - b.vel.x) == sgn(a.a.x - b.a.x))
			return;
		av = &a.vel.x;
		bv = &b.vel.x;
	}
	else if(n == 1)
	{
		if(sgn(a.vel.y - b.vel.y) == sgn(a.a.y - b.a.y))
			return;
		av = &a.vel.y;
		bv = &b.vel.y;
	}
	else
	{
		if(sgn(a.vel.z - b.vel.z) == sgn(a.a.z - b.a.z))
			return;
		av = &a.vel.z;
		bv = &b.vel.z;
	}
	double avt = *av;
	double bvt = *bv;

	if(!a.frozen && !b.frozen)
	{
		*av = (avt * (a.mass - b.mass) + 2. * b.mass * bvt) / (a.mass + b.mass);
		*bv = (bvt * (b.mass - a.mass) + 2. * a.mass * avt) / (b.mass + a.mass);
	}
	else if(a.frozen)
		*bv = -bvt;
	else
		*av = -avt;
}

void PhysicsProcessor::collide(BoxPH &a, BoxPH &b)
{
	if(a.frozen && b.frozen)
		return;

	double dx = intervalIntersection(a.a.x - a.d.x, a.a.x + a.d.x, b.a.x - b.d.x, b.a.x + b.d.x);
	if(dx <= EPS)
		return;
	int n = 0;
	double dy = intervalIntersection(a.a.y - a.d.y, a.a.y + a.d.y, b.a.y - b.d.y, b.a.y + b.d.y);
	if(dy <= EPS)
		return;
	if(dy < dx)
		n = 1;
	double dz = intervalIntersection(a.a.z - a.d.z, a.a.z + a.d.z, b.a.z - b.d.y, b.a.z + b.d.y);
	if(dz <= EPS)
		return;
	if(dz < dx && dz < dy)
		n = 2;

	double *av = 0, *bv = 0;
	if(!n)
	{
		if(sgn(a.vel.x - b.vel.x) == sgn(a.a.x - b.a.x))
			return;
		av = &a.vel.x;
		bv = &b.vel.x;
	}
	else if(n == 1)
	{
		if(sgn(a.vel.y - b.vel.y) == sgn(a.a.y - b.a.y))
			return;
		av = &a.vel.y;
		bv = &b.vel.y;
	}
	else
	{
		if(sgn(a.vel.z - b.vel.z) == sgn(a.a.z - b.a.z))
			return;
		av = &a.vel.z;
		bv = &b.vel.z;
	}
	double avt = *av;
	double bvt = *bv;

	if(!a.frozen && !b.frozen)
	{
		*av = (avt * (a.mass - b.mass) + 2. * b.mass * bvt) / (a.mass + b.mass);
		*bv = (bvt * (b.mass - a.mass) + 2. * a.mass * avt) / (b.mass + a.mass);
	}
	else if(a.frozen)
		*bv = -bvt;
	else
		*av = -avt;
}

void PhysicsProcessor::collide(BoxPH &a, CubePH &b)
{
	if(a.frozen && b.frozen)
		return;

	double dx = intervalIntersection(a.a.x - a.d.x, a.a.x + a.d.x, b.a.x - b.d, b.a.x + b.d);
	if(dx <= EPS)
		return;
	int n = 0;
	double dy = intervalIntersection(a.a.y - a.d.y, a.a.y + a.d.y, b.a.y - b.d, b.a.y + b.d);
	if(dy <= EPS)
		return;
	if(dy < dx)
		n = 1;
	double dz = intervalIntersection(a.a.z - a.d.z, a.a.z + a.d.z, b.a.z - b.d, b.a.z + b.d);
	if(dz <= EPS)
		return;
	if(dz < dx && dz < dy)
		n = 2;

	double *av = 0, *bv = 0;
	if(!n)
	{
		if(sgn(a.vel.x - b.vel.x) == sgn(a.a.x - b.a.x))
			return;
		av = &a.vel.x;
		bv = &b.vel.x;
	}
	else if(n == 1)
	{
		if(sgn(a.vel.y - b.vel.y) == sgn(a.a.y - b.a.y))
			return;
		av = &a.vel.y;
		bv = &b.vel.y;
	}
	else
	{
		if(sgn(a.vel.z - b.vel.z) == sgn(a.a.z - b.a.z))
			return;
		av = &a.vel.z;
		bv = &b.vel.z;
	}
	double avt = *av;
	double bvt = *bv;

	if(!a.frozen && !b.frozen)
	{
		*av = (avt * (a.mass - b.mass) + 2. * b.mass * bvt) / (a.mass + b.mass);
		*bv = (bvt * (b.mass - a.mass) + 2. * a.mass * avt) / (b.mass + a.mass);
	}
	else if(a.frozen)
		*bv = -bvt;
	else
		*av = -avt;
}

void PhysicsProcessor::collide(CubePH &a, BoxPH &b)
{
	collide(b, a);
}

void PhysicsProcessor::collide(PhysicsObject *a, PhysicsObject *b)
{
	if(CubePH *p = dynamic_cast<CubePH*>(a))
	{
		if(CubePH *p1 = dynamic_cast<CubePH*>(b))
			collide(*p, *p1);
		else if(SquareAAPH *p1 = dynamic_cast<SquareAAPH*>(b))
			collide(*p, *p1);
	}
	else if(BoxPH *p = dynamic_cast<BoxPH*>(a))
	{
		if(CubePH *p1 = dynamic_cast<CubePH*>(b))
			collide(*p, *p1);
		else if(BoxPH *p1 = dynamic_cast<BoxPH*>(b))
			collide(*p, *p1);
	}
}

void PhysicsProcessor::collide(CubePH &a, SquareAAPH &b)
{
}

void PhysicsProcessor::collide(SquareAAPH &a, CubePH &b)
{
	collide(b, a);
}

void PhysicsProcessor::collide(SquareAAPH &b, SquareAAPH &a)
{
}


void PhysicsProcessor::updateList(double dt)
{
	for(list<PhysicsObject*>::iterator it = phList.begin(); it != phList.end(); ++it)
		(*it)->update(dt);

	for(list<PhysicsObject*>::iterator it = phList.begin(); it != phList.end(); ++it)
	{
		list<PhysicsObject*>::iterator it2 = it;
		++it2;
		for(; it2 != phList.end(); ++it2)
			collide(*it, *it2);
	}
}
