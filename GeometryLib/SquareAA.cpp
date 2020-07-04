#include "SquareAA.h"

const Vector SquareAA::normals[6] = 
{
	Vector( 1.,  0.,  0.),
	Vector( 0.,  1.,  0.),
	Vector( 0.,  0.,  1.),
	Vector(-1.,  0.,  0.),
	Vector( 0., -1.,  0.),
	Vector( 0.,  0., -1.)
};

const Vector SquareAA::vertices[6][4] =
{
	{Vector( 0.,  1.,  1.), Vector( 0., -1.,  1.), Vector( 0., -1., -1.), Vector( 0.,  1., -1.)},
	{Vector( 1.,  0., -1.), Vector(-1.,  0., -1.), Vector(-1.,  0.,  1.), Vector( 1.,  0.,  1.)},
	{Vector( 1.,  1.,  0.), Vector(-1.,  1.,  0.), Vector(-1., -1.,  0.), Vector( 1., -1.,  0.)},
	{Vector( 0., -1.,  1.), Vector( 0.,  1.,  1.), Vector( 0.,  1., -1.), Vector( 0., -1., -1.)},
	{Vector(-1.,  0., -1.), Vector( 1.,  0., -1.), Vector( 1.,  0.,  1.), Vector(-1.,  0.,  1.)},
	{Vector(-1.,  1.,  0.), Vector( 1.,  1.,  0.), Vector( 1., -1.,  0.), Vector(-1., -1.,  0.)}
};

SquareAA::SquareAA(void) :
	a(Vector(1, 0, 0)), d(1), dir(XP)
{
}

SquareAA::SquareAA(const Vector &_a, double _d, AxisDirection _dir) :
	a(_a), d(_d), dir(_dir)
{
}

SquareAA::~SquareAA(void)
{
}

Vector SquareAA::normal() const
{
	return normals[dir];
}

Vector SquareAA::getVertex(int index) const
{
	return vertices[dir][index] * d + a;
}

bool SquareAA::containsPoint(const Vector &v) const
{
	return
		(dir == XP || dir == XN) && abs(v.x - a.x) <= EPS &&
		isBetween(v.y, a.y - d, a.y + d) &&
		isBetween(v.z, a.z - d, a.z + d) ||
		(dir == YP || dir == YN) && abs(v.y - a.y) <= EPS &&
		isBetween(v.z, a.z - d, a.z + d) &&
		isBetween(v.x, a.x - d, a.x + d) ||
		(dir == ZP || dir == ZN) && abs(v.z - a.z) <= EPS &&
		isBetween(v.x, a.x - d, a.x + d) &&
		isBetween(v.y, a.y - d, a.y + d);
}

bool SquareAA::containsPointInPlane(const Vector &v) const
{
	return
		(dir == XP || dir == XN) &&
		isBetween(v.y, a.y - d, a.y + d) &&
		isBetween(v.z, a.z - d, a.z + d) ||
		(dir == YP || dir == YN) &&
		isBetween(v.z, a.z - d, a.z + d) &&
		isBetween(v.x, a.x - d, a.x + d) ||
		(dir == ZP || dir == ZN) &&
		isBetween(v.x, a.x - d, a.x + d) &&
		isBetween(v.y, a.y - d, a.y + d);
}

Vector SquareAA::getPos() const
{
	return a;
}

void SquareAA::setPos(const Vector &_v)
{
	a = _v;
}
