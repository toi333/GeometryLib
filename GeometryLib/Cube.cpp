#include "Cube.h"

using namespace std;

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
	blah = 0;
	d = 1.;
}

Cube::Cube(const Vector &_a, double _d)
	: a(_a), d(_d)
{
	blah = 0;
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

Vector Cube::getPos() const
{
	return a;
}

double Cube::volume() const
{
	return d * d * d * 8.;
}

pair<double, Vector> Cube::reflect(const Ray &r) const
{
	double mn = INF;
	Vector n;
	for(int i = 0; i < 6; ++i)
	{
		double a = r.hit(getSide(i));
		if(a < mn && a > EPS)
		{
			mn = a;
			n = getNormal(i);
		}
	}
	return pair<double, Vector>(mn, n);
}

void Cube::setPos(const Vector &_v)
{
	a = _v;
}
