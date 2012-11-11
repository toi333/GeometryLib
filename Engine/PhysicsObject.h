#pragma once
#include "Vector.h"
#include <list>

enum PHType
{
	CUBEPH
};

class PhysicsObject
{
public:
	Vector vel;

	PhysicsObject(void);
	PhysicsObject(Vector _vel);
	~PhysicsObject(void);

	virtual Vector pos() = 0;
	virtual void update(double dt) = 0;
	//virtual bool collide(const PhysicsObject *p, Vector &n) const = 0;
	//virtual PHType phtype() const = 0;

	static std::list<PhysicsObject*> phList;
	static void updateList(double dt);
};
