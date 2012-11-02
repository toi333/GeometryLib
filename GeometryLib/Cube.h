#pragma once
#include "PointSet.h"
#include "Vector.h"

class Cube :
	public PointSet
{
public:
	Vector a;
	double d;

	Vector getVertex(int index);
	Vector getNormal(int index);

	PSType type() const;

	Cube(void);
	Cube(const Vector &_a, double _d);
	~Cube(void);
};

