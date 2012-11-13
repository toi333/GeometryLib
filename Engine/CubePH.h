#pragma once

#include "PhysicsObject.h"
#include "Cube.h"

class CubePH :
	public PhysicsObject, public Cube
{
public:
	CubePH(void);
	CubePH(Cube cb, Vector _vel);
	~CubePH(void);

	Vector pos();
	void update(double dt);
};
