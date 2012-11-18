#pragma once

#include "Vector.h"
#include "PointSet.h"

class PhysicsObject
{
public:
	Vector vel;
	double mass;
	bool frozen;
	PhysicsObject *flr;

	PhysicsObject(void);
	PhysicsObject(Vector _vel);
	PhysicsObject(Vector _vel, double _mass, bool _frozen);
	~PhysicsObject(void);

	virtual Vector getPos() const = 0;
	virtual void setPos(const Vector &_v) = 0;
	virtual void update(double dt) = 0;

	static Vector gravity;
	static double collisionElasticity;
	static double collisionFriction;
};