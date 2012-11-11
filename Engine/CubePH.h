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

	PHType phtype() const;
	bool collide(const PhysicsObject *p, Vector &n) const;
	bool collide(const CubePH *p, Vector &n) const;
	Vector pos();
	void update(double dt);
};
