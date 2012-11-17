#pragma once

#include "PhysicsObject.h"
#include "Cube.h"

class CubePH :
	public PhysicsObject, public Cube
{
public:
	CubePH(void);
	CubePH(const Cube &cb);
	CubePH(const Cube &cb, const Vector &_vel);
	CubePH(const Cube &cb, const Vector &_vel, double _mass, bool _frozen);
	~CubePH(void);

	Vector pos();
	void update(double dt);
};
