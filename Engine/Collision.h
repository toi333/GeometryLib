#pragma once

#include "Vector.h"
#include "CubePH.h"

class Collision
{
public:
	double t;
	Vector n;

	Collision(void);
	Collision(double _t, const Vector &_n);
	~Collision(void);

	void collide(const CubePH &a, const CubePH &b);
};

