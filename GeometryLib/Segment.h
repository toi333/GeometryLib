#pragma once

#include "PointSet.h"
#include "Vector.h"

class Segment :
	public PointSet
{
public:
	Segment(void);
	Segment(const Vector &_a, const Vector &_b);
	~Segment(void);

	double length() const;
	double length2() const;
	PSType type();

	Vector a, b;
private:
};