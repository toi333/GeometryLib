#include "StdAfx.h"
#include "Triangle.h"

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

PSType Triangle::type() const
{
	return TRIANGLE;
}
