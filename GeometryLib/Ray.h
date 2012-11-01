#pragma once

#include "PointSet.h"
#include "Vector.h"

class Ray :
	public PointSet
{
public:
	Ray(void);
	Ray(const Vector &_a, const Vector &_b);
	~Ray(void);

	PSType type();

	Vector a, b;
private:
};