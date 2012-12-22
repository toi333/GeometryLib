#include "StdAfx.h"
#include "RectangleAA.h"

enum AxisDirection
{
	XP,
	YP,
	ZP,
	XN,
	YN,
	ZN
};

const Vector RectangleAA::normals[6] = 
{
	Vector( 1.,  0.,  0.),
	Vector( 0.,  1.,  0.),
	Vector( 0.,  0.,  1.),
	Vector(-1.,  0.,  0.),
	Vector( 0., -1.,  0.),
	Vector( 0.,  0., -1.)
};

const Vector RectangleAA::vertices[6][4] =
{
	{Vector( 0.,  1.,  1.), Vector( 0., -1.,  1.), Vector( 0., -1., -1.), Vector( 0.,  1., -1.)},
	{Vector( 1.,  0., -1.), Vector(-1.,  0., -1.), Vector(-1.,  0.,  1.), Vector( 1.,  0.,  1.)},
	{Vector( 1.,  1.,  0.), Vector(-1.,  1.,  0.), Vector(-1., -1.,  0.), Vector( 1., -1.,  0.)},
	{Vector( 0., -1.,  1.), Vector( 0.,  1.,  1.), Vector( 0.,  1., -1.), Vector( 0., -1., -1.)},
	{Vector(-1.,  0., -1.), Vector( 1.,  0., -1.), Vector( 1.,  0.,  1.), Vector(-1.,  0.,  1.)},
	{Vector(-1.,  1.,  0.), Vector( 1.,  1.,  0.), Vector( 1., -1.,  0.), Vector(-1., -1.,  0.)}
};

RectangleAA::RectangleAA(void) :
a(Vector(1, 0, 0)), d(Vector(1, 1, 1)), dir(XP)
{
}

RectangleAA::RectangleAA(const Vector &_a, const Vector &_d, AxisDirection _dir) :
a(_a), d(_d), dir(_dir)
{
}

RectangleAA::~RectangleAA(void)
{
}

Vector RectangleAA::normal() const
{
	return normals[dir];
}

Vector RectangleAA::getVertex(int index) const
{
	return pairwiseProduct(vertices[dir][index], d) + a;
}

bool RectangleAA::containsPoint(const Vector &v) const
{
	return
		(dir == XP || dir == XN) && abs(v.x - a.x) <= EPS &&
		isBetween(v.y, a.y - d.y, a.y + d.y) &&
		isBetween(v.z, a.z - d.z, a.z + d.z) ||
		(dir == YP || dir == YN) && abs(v.y - a.y) <= EPS &&
		isBetween(v.z, a.z - d.z, a.z + d.z) &&
		isBetween(v.x, a.x - d.x, a.x + d.x) ||
		(dir == ZP || dir == ZN) && abs(v.z - a.z) <= EPS &&
		isBetween(v.x, a.x - d.x, a.x + d.x) &&
		isBetween(v.y, a.y - d.y, a.y + d.y);
}

bool RectangleAA::containsPointInPlane(const Vector &v) const
{
	return
		(dir == XP || dir == XN) &&
		isBetween(v.y, a.y - d.y, a.y + d.y) &&
		isBetween(v.z, a.z - d.z, a.z + d.z) ||
		(dir == YP || dir == YN) &&
		isBetween(v.z, a.z - d.z, a.z + d.z) &&
		isBetween(v.x, a.x - d.x, a.x + d.x) ||
		(dir == ZP || dir == ZN) &&
		isBetween(v.x, a.x - d.x, a.x + d.x) &&
		isBetween(v.y, a.y - d.y, a.y + d.y);
}

Vector RectangleAA::getPos() const
{
	return a;
}

void RectangleAA::setPos(const Vector &_v)
{
	a = _v;
}
