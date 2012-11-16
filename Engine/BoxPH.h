#pragma once

#include "PhysicsObject.h"
#include "Box.h"

class BoxPH :
	public PhysicsObject, public Box
{
public:
	BoxPH(void);
	BoxPH(const Box &bx);
	BoxPH(const Box &bx, const Vector &_vel);
	BoxPH(const Box &bx, const Vector &_vel, double _mass, bool _frozen);
	~BoxPH(void);

	Vector pos();
	void update(double dt);
};
