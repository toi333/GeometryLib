#pragma once

#include "Vector.h"
#include "CubePH.h"
#include "SquareAAPH.h"
#include "PhysicsObject.h"
#include <list>

class PhysicsProcessor
{
public:
	PhysicsProcessor(void);
	~PhysicsProcessor(void);

	void collide(PhysicsObject *a, PhysicsObject *b);
	void collide(CubePH &a, CubePH &b);
	void collide(CubePH &a, SquareAAPH &b);
	void collide(SquareAAPH &a, CubePH &b);
	void collide(SquareAAPH &b, SquareAAPH &a);

	std::list<PhysicsObject*> phList;
	void updateList(double dt);
};

