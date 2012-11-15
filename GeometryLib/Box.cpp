#include "StdAfx.h"
#include "Box.h"

using namespace std;

const Vector Box::normals[6] = 
{
	Vector( 1.,  0.,  0.),
	Vector( 0.,  1.,  0.),
	Vector( 0.,  0.,  1.),
	Vector(-1.,  0.,  0.),
	Vector( 0., -1.,  0.),
	Vector( 0.,  0., -1.)
};

const Vector Box::vertices[8] =
{
	Vector( 1.,  1.,  1.), Vector( 1.,  1., -1.),
	Vector( 1., -1.,  1.), Vector( 1., -1., -1.),
	Vector(-1.,  1.,  1.), Vector(-1.,  1., -1.),
	Vector(-1., -1.,  1.), Vector(-1., -1., -1.)
};

Box::Box(void)
{
}

Box::Box(const Vector &_a, const Vector &_d)
	: a(_a), d(_d)
{
}

Box::~Box(void)
{
}

Vector Box::getVertex(int index) const
{
	return a + pairwiseProduct(vertices[index], d);
}

Vector Box::getNormal(int index) const
{
	return normals[index];
}

RectangleAA Box::getSide(int index) const
{
	return RectangleAA(a + pairwiseProduct(normals[index], d), d, (AxisDirection)index);
}

Vector Box::pos() const
{
	return a;
}

double Box::volume() const
{
	return d.x * d.y * d.z * 8.;
}

pair<double, Vector> Box::reflect(const Ray &r) const
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
