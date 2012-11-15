#pragma once

#include "PointSet.h"
#include "Vector.h"
#include "Surfaces.h"

class Ray :
	public PointSet
{
public:
	Vector a, b;

	Ray(void);
	Ray(const Vector &_a, const Vector &_b);
	~Ray(void);

	double hit(Surface *sf) const;
	double hit(const Plane &pi) const;
	double hit(const Triangle &t) const;
	double hit(const SquareAA &sq) const;
	double hit(const RectangleAA &sq) const;

	Vector pos() const;
private:
};