#pragma once
#include "Vector.h"
#include <list>

class PhysicsObject
{
public:
	PhysicsObject(void);
	PhysicsObject(Vector _vel);
	~PhysicsObject(void);

	virtual Vector pos() = 0;
	virtual void update(double dt) = 0;

	Vector vel;

	static std::list<PhysicsObject*> phList;
	static void updateList(double dt);
};

