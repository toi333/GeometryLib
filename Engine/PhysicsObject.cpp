#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(void)
	: vel(Vector()), mass(1), frozen(0), flr(0)
{
}

PhysicsObject::PhysicsObject(Vector _vel)
	: vel(_vel), mass(1), frozen(0), flr(0)
{
}

PhysicsObject::PhysicsObject(Vector _vel, double _mass, bool _frozen)
	: vel(_vel), mass(_mass), frozen(_frozen), flr(0)
{
}

PhysicsObject::~PhysicsObject(void)
{
}

double PhysicsObject::collisionElasticity = 0.3;
double PhysicsObject::collisionFriction = 0.1;
Vector PhysicsObject::gravity = Vector(0, 0, 0);
