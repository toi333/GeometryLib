#pragma once

#include "PointSet.h"
#include "SquareAA.h"

class Cube :
	public PointSet
{
public:
	Vector a;
	double d;

	Cube(void);
	Cube(const Vector &_a, double _d);
	~Cube(void);

	Vector getVertex(int index) const;
	Vector getNormal(int index) const;
	SquareAA getSide(int index) const;
	PSType type() const;

private:
	static const Vector normals[6];
	static const Vector vertices[8];
};
