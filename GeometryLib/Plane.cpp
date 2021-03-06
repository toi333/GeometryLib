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

Plane::Plane(const Surface &sf)
{
	p = sf.getPos();
	n = sf.normal();
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

Vector Plane::getPos() const
{
	return p;
}

void Plane::setPos(const Vector &_v)
{
	p = _v;
}
