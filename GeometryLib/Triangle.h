#pragma once

#include "PointSet.h"
#include "Vector.h"
#include "Segment.h"

class Triangle :
	public PointSet
{
public:
	Triangle(void);
	Triangle(Vector &_a, Vector &_b, Vector &_c);
	~Triangle(void);

	double area(void) const;
	double ccw(const Vector &v) const;
	Vector normal(void) const;
	void flip(void);
	Vector getVertex(int x) const;
	Segment getSegment(int x) const;
	PSType type() const;

	Vector a, b, c;
};

