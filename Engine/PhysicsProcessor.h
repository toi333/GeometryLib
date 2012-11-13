#pragma once

#include "Vector.h"
#include "CubePH.h"
#include "PhysicsObject.h"
#include <list>

class PhysicsProcessor
{
public:
	PhysicsProcessor(void);
	~PhysicsProcessor(void);

	void collide(PhysicsObject *a, PhysicsObject *b);
	void collide(CubePH &a, CubePH &b);

	bool impact(PhysicsObject *a, PhysicsObject *b);

	std::list<PhysicsObject*> phList;
	void updateList(double dt);
};

