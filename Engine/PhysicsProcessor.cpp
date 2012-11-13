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
	
}

void PhysicsProcessor::collide(PhysicsObject *a, PhysicsObject *b)
{
	if(CubePH *p = dynamic_cast<CubePH*>(a))
	{
		if(CubePH *p1 = dynamic_cast<CubePH*>(b))
			collide(*p, *p1);
	}
}

bool PhysicsProcessor::impact(PhysicsObject *a, PhysicsObject *b)
{
	return false;
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
