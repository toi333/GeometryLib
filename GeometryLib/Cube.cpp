#include "StdAfx.h"
#include "Cube.h"


Cube::Cube(void)
{
	d = 1.;
}

Cube::Cube(const Vector &_a, double _d)
	: a(_a), d(_d)
{
}

Cube::~Cube(void)
{
}

Vector Cube::getVertex(int index)
{
	switch(index)
	{
	case 0:
		return a + Vector(-d, -d, d);
		break;
	case 1:
		return a + Vector(d, -d, d);
		break;
	case 2:
		return a + Vector(-d, -d, -d);
		break;
	case 3:
		return a + Vector(d, -d, -d);
		break;
	case 4:
		return a + Vector(-d, d, d);
		break;
	case 5:
		return a + Vector(d, d, d);
		break;
	case 6:
		return a + Vector(-d, d, -d);
		break;
	case 7:
		return a + Vector(d, d, -d);
		break;
	default:
		return a;
		break;
	}
}

Vector Cube::getNormal(int index)
{
	switch(index)
	{
	case 0:
		return Vector(0., -1., 0.);
		break;
	case 1:
		return Vector(0., 0., 1.);
		break;
	case 2:
		return Vector(1., 0., 0.);
		break;
	case 3:
		return Vector(0., 1., 0.);
		break;
	case 4:
		return Vector(0., 0., -1.);
		break;
	case 5:
		return Vector(-1., 0., 0.);
		break;
	default:
		return Vector(0., 0., 1.);
		break;
	}
}

PSType Cube::type() const
{
	return CUBE;
}

SquareAA Cube::getSide(int index)
{
	switch(index)
	{
	case 0:
		return SquareAA(a - Vector(0., d, 0.), d, YN);
		break;
	case 1:
		return SquareAA(a + Vector(0., 0., d), d, ZP);
		break;
	case 2:
		return SquareAA(a + Vector(d, 0., 0.), d, XP);
		break;
	case 3:
		return SquareAA(a + Vector(0., d, 0.), d, YP);
		break;
	case 4:
		return SquareAA(a - Vector(0., 0., d), d, ZN);
		break;
	case 5:
		return SquareAA(a - Vector(d, 0., 0.), d, XN);
		break;
	default:
		return SquareAA(a, d, XP);
		break;
	}
}
