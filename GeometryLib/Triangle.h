#pragma once

#include "Surface.h"
#include "Segment.h"

class Triangle :
	public Surface
{
public:
	Vector a, b, c;

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
};

