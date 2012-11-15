#pragma once

#include "Vector.h"

class PhysicsObject
{
public:
	Vector vel;
	double mass;
	bool frozen;

	PhysicsObject(void);
	PhysicsObject(Vector _vel);
	PhysicsObject(Vector _vel, double _mass, bool _frozen);
	~PhysicsObject(void);

	virtual Vector pos() = 0;
	virtual void update(double dt) = 0;
};