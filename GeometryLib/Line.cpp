#include "StdAfx.h"
#include "Line.h"

Line::Line(void)
{
}

Line::Line(const Vector &_a, const Vector &_b)
{
	a = _a;
	b = _b - _a;
}

Line::Line(const Ray &r)
{
	a = r.a;
	b = r.b;
}

Line::Line(const Segment &s)
{
	a = s.a;
	b = s.a - s.b;
}

Line::~Line(void)
{
}

PSType Line::type() const
{
	return LINE;
}
