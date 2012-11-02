#pragma once

#include "GeometryLib.h"
#include "Essential.h"
#include "DrawEngine.h"

class RayCast :
	public Ray
{
public:
	RayCast(void);
	RayCast(const Ray &r);
	~RayCast(void);
	
	double hit(const Plane &pi);
	double hit(const Triangle &t);
	double hit(PointSet *p);
	void cast(int maxBounces = 100);
};
