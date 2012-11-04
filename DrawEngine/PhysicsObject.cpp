#include "StdAfx.h"
#include "PhysicsObject.h"

using namespace std;

list<PhysicsObject*> PhysicsObject::phList;

PhysicsObject::PhysicsObject(void)
{
}

PhysicsObject::PhysicsObject(Vector _vel) :
	vel(_vel)
{
}

PhysicsObject::~PhysicsObject(void)
{
}

void PhysicsObject::updateList(double dt)
{
	for(list<PhysicsObject*>::iterator it = phList.begin(); it != phList.end(); ++it)
		(*it)->update(dt);
}
