#include "StdAfx.h"
#include "SquareAA.h"


SquareAA::SquareAA(void)
{
}

SquareAA::SquareAA(const Vector &_a, double _d, AxisDirection _dir)
{
	a = _a;
	d = _d;
	dir = _dir;
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

const Vector SquareAA::normals[6] = 
{
	Vector(1., 0., 0.),
	Vector(0., 1., 0.),
	Vector(0., 0., 1.),
	Vector(-1., 0., 0.),
	Vector(0., -1., 0.),
	Vector(0., 0., -1.)
};

const Vector SquareAA::vertices[6][4] =
{
	{Vector(0., 1., 1.), Vector(0., -1., 1.), Vector(0., -1., -1.), Vector(0., 1., -1.)},
	{Vector(1., 0., 1.), Vector(-1., 0., 1.), Vector(-1., 0., -1.), Vector(1., 0., -1.)},
	{Vector(1., 1., 0.), Vector(-1., 1., 0.), Vector(-1., -1., 0.), Vector(1., -1., 0.)},
	{Vector(0., -1., -1.), Vector(0., 1., -1.), Vector(0., 1., 1.), Vector(0., -1., 1.)},
	{Vector(-1., 0., -1.), Vector(1., 0., -1.), Vector(1., 0., 1.), Vector(-1., 0., 1.)},
	{Vector(-1., -1., 0.), Vector(1., -1., 0.), Vector(1., 1., 0.), Vector(-1., 1., 0.)}
};

PSType SquareAA::type() const
{
	return SQUAREAA;
}

