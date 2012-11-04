#include "StdAfx.h"
#include "Cube.h"

const Vector Cube::normals[6] = 
{
	Vector( 1.,  0.,  0.),
	Vector( 0.,  1.,  0.),
	Vector( 0.,  0.,  1.),
	Vector(-1.,  0.,  0.),
	Vector( 0., -1.,  0.),
	Vector( 0.,  0., -1.)
};

const Vector Cube::vertices[8] =
{
	Vector( 1.,  1.,  1.), Vector( 1.,  1., -1.),
	Vector( 1., -1.,  1.), Vector( 1., -1., -1.),
	Vector(-1.,  1.,  1.), Vector(-1.,  1., -1.),
	Vector(-1., -1.,  1.), Vector(-1., -1., -1.)
};

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

Vector Cube::getVertex(int index) const
{
	return a + vertices[index] * d;
}

Vector Cube::getNormal(int index) const
{
	return normals[index];
}

SquareAA Cube::getSide(int index) const
{
	return SquareAA(a + normals[index] * d, d, (AxisDirection)index);
}

PSType Cube::type() const
{
	return CUBE;
}
