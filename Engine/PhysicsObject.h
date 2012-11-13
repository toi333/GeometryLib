#pragma once

#include "Vector.h"

class PhysicsObject
{
public:
	Vector vel;

	PhysicsObject(void);
	PhysicsObject(Vector _vel);
	~PhysicsObject(void);

	virtual Vector pos() = 0;
	virtual void update(double dt) = 0;
};