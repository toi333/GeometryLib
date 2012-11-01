#include "StdAfx.h"
#include "Segment.h"

Segment::Segment(void)
{
}

Segment::Segment(const Vector &_a, const Vector &_b)
{
	a = _a;
	b = _b;
}

Segment::~Segment(void)
{
}

double Segment::length() const
{
	return a.distance(b);
}

double Segment::length2() const
{
	return a.distance2(b);
}

PSType Segment::type()
{
	return SEGMENT;
}