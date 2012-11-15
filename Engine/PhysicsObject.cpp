#include "StdAfx.h"
#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(void)
{
}

PhysicsObject::PhysicsObject(Vector _vel)
	: vel(_vel), mass(1), frozen(0)
{
}

PhysicsObject::PhysicsObject(Vector _vel, double _mass, bool _frozen)
	: vel(_vel), mass(_mass), frozen(_frozen)
{
}

PhysicsObject::~PhysicsObject(void)
{
}
