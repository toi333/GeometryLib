#pragma once

#include "GeometryLib.h"
#include "Essential.h"

class RayCast
{
public:
	Ray r;

	RayCast(void);
	RayCast(const Ray &_r);
	~RayCast(void);

	double hit(PointSet *p);
	double hit(const Plane &pi);
	double hit(const Triangle &t);
	double hit(const SquareAA &sq);
};
