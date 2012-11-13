#include "StdAfx.h"
#include "Plane.h"

Plane::Plane(void)
{
}

Plane::Plane(const Vector &_p, const Vector &_n)
{
	p = _p;
	n = _n.normalized();
}

Plane::Plane(const Vector &a, const Vector &b, const Vector &c)
{
	p = a;
	n = crossProduct(b - a, c - a).normalize();
}

Plane::Plane(const Triangle &tri)
{
	p = tri.a;
	n = tri.normal();
}

Plane::Plane(const SquareAA &sq)
{
	p = sq.a;
	n = sq.normal();
}

Plane::~Plane(void)
{
}

Vector Plane::normal() const
{
	return n;
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

bool Plane::containsPoint(const Vector &v) const
{
	return abs(dotProduct(v - p, n)) <= EPS;
}

bool Plane::containsPointInPlane(const Vector &v) const
{
	return true;
}

PSType Plane::type() const
{
	return PLANE;
}
