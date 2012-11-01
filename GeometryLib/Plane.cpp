#include "StdAfx.h"
#include "Plane.h"

Plane::Plane(void)
{
}

Plane::Plane(const Vector &_p, const Vector &_n)
{
	p = _p;
	n = _n;
}

Plane::Plane(const Vector &a, const Vector &b, const Vector &c)
{
	p = a;
	n = crossProduct(b - a, c - a).normalize();
}

Plane::Plane(const Triangle &tri)
{
	p = tri.a;
	n = crossProduct(tri.b - tri.a, tri.c - tri.a).normalize();
}

Plane::~Plane(void)
{
}

double Plane::a() const
{
	return n.x;
}

double Plane::b() const
{
	return n.y;
}

double Plane::c() const
{
	return n.z;
}

double Plane::d() const
{
	return -dotProduct(n, p);
}

PSType Plane::type()
{
	return PLANE;
}