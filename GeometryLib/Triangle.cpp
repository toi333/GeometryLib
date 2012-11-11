#include "StdAfx.h"
#include "Triangle.h"
#include "Essential.h"
#include "Plane.h"

using namespace std;

Triangle::Triangle(void)
{
}

Triangle::Triangle(Vector &_a, Vector &_b, Vector &_c)
{
	a = _a;
	b = _b;
	c = _c;
}

Triangle::~Triangle(void)
{
}

double Triangle::area(void) const
{
	return crossProduct(b - a, c - a).length() / 2.;
}

double Triangle::ccw(const Vector &v) const
{
	return mixedProduct(v, b - a, c - a);
}

Vector Triangle::normal(void) const
{
	return crossProduct(b - a, c - a).normalize();
}

void Triangle::flip(void)
{
	swap(a, b);
}

Vector Triangle::getVertex(int x) const
{
	switch(x)
	{
	case 0:
		return a;
	case 1:
		return b;
	case 2:
		return c;
	default:
		return Vector();
	}
}

Segment Triangle::getSegment(int x) const
{
	switch(x)
	{
	case 0:
		return Segment(a, b);
	case 1:
		return Segment(b, c);
	case 2:
		return Segment(c, a);
	default:
		return Segment(Vector(), Vector(1, 0, 0));
	}
}

bool Triangle::containsPoint(const Vector &v) const
{
	if(!Plane(*this).containsPoint(v))
		return false;
	return containsPointInPlane(v);
}

bool Triangle::containsPointInPlane(const Vector &v) const
{
	double ccw1 = sgn(ccw(crossProduct(a - c, v - c)));
	double ccw2 = sgn(ccw(crossProduct(b - a, v - a)));
	double ccw3 = sgn(ccw(crossProduct(c - b, v - b)));
	return min(a, b, c) != -max(a, b, c);
}


PSType Triangle::type() const
{
	return TRIANGLE;
}