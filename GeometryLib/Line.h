#pragma once

#include "PointSet.h"
#include "Vector.h"
#include "Ray.h"
#include "Segment.h"

class Line :
	public PointSet
{
public:
	Vector a, b;

	Line(void);
	Line(const Vector &_a, const Vector &_b);
	Line(const Ray &r);
	Line(const Segment &s);
	~Line(void);

};
