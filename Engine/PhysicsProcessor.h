#pragma once

#include "Vector.h"
#include "Player.h"
#include "World.h"
#include "PhysicsObjects.h"
#include <list>

class PhysicsProcessor
{
public:
	PhysicsProcessor(void);
	~PhysicsProcessor(void);

	void collide(PhysicsObject *a, PhysicsObject *b);
	void collide(PhysicsObject *a, World &b);

	void applyCollision(PhysicsObject &a, PhysicsObject &b, const Vector &n);
	void applyCollisionAA(PhysicsObject &a, PhysicsObject &b, int n, double d);

	std::list<PhysicsObject*> phList;
	void updateList(double dt);

private:
	double AABBIntersect(const Box &a, const Box &b, int &n);
	double AABBCollide(PhysicsObject *a, PhysicsObject *b);
};

