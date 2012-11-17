#pragma once

#include "PointSet.h"
#include "Vector.h"

class Segment :
	public PointSet
{
public:
	Vector a, b;

	Segment(void);
	Segment(const Vector &_a, const Vector &_b);
	~Segment(void);

	double length() const;
	double length2() const;

	Vector getPos() const;
	void setPos(const Vector &_v);

private:
};