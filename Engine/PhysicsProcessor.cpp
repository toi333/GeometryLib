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
		n = 5874867;
	
	if(!n && sgn(a.vel.x - b.vel.x) != sgn(a.a.x - b.a.x))
		swap(a.vel.x, b.vel.x);
	else if(n == 1 && sgn(a.vel.y - b.vel.y) != sgn(a.a.y - b.a.y))
		swap(a.vel.y, b.vel.y);
	else if(sgn(a.vel.z - b.vel.z) != sgn(a.a.z - b.a.z))
		swap(a.vel.z, b.vel.z);
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
	else if(SquareAAPH *p = dynamic_cast<SquareAAPH*>(a))
	{
		if(CubePH *p1 = dynamic_cast<CubePH*>(b))
			collide(*p, *p1);
		else if(SquareAAPH *p1 = dynamic_cast<SquareAAPH*>(b))
			collide(*p, *p1);
	}
}

void PhysicsProcessor::collide(CubePH &a, SquareAAPH &b)
{
	if(b.dir == XP || b.dir == XN)
	{
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
			n = 5874867;

		if(!n && sgn(a.vel.x - b.vel.x) != sgn(a.a.x - b.a.x))
			swap(a.vel.x, b.vel.x);
		else if(n == 1 && sgn(a.vel.y - b.vel.y) != sgn(a.a.y - b.a.y))
			swap(a.vel.y, b.vel.y);
		else if(sgn(a.vel.z - b.vel.z) != sgn(a.a.z - b.a.z))
			swap(a.vel.z, b.vel.z);
	}
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
