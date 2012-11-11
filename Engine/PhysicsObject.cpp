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

	for(list<PhysicsObject*>::iterator it = phList.begin(); it != phList.end(); ++it)
	{
		list<PhysicsObject*>::iterator jt = it;
		++jt;
		for(; jt != phList.end(); ++jt)
		{}//if()
}
