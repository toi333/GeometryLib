#pragma once

#include "PointSet.h"
#include "Vector.h"

class Ray :
	public PointSet
{
public:
	Vector a, b;

	Ray(void);
	Ray(const Vector &_a, const Vector &_b);
	~Ray(void);

private:
};