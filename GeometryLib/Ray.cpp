#include "StdAfx.h"
#include "Ray.h"

Ray::Ray(void)
{
}

Ray::Ray(const Vector &_a, const Vector &_b)
{
	a = _a;
	b = _b - _a;
}

Ray::~Ray(void)
{
}

PSType Ray::type() const
{
	return RAY;
}