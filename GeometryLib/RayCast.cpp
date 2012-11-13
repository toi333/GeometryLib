#include "StdAfx.h"
#include "RayCast.h"

using namespace std;

RayCast::RayCast(void)
{
}

RayCast::RayCast(const Ray &_r)
{
	r = _r;
}

RayCast::~RayCast(void)
{
}

double RayCast::hit(PointSet *p)
{
	if(Plane *pp = dynamic_cast<Plane*>(p))
		return hit(*pp);
	else if(Triangle *pp = dynamic_cast<Triangle*>(p))
		return hit(*pp);
	else if(SquareAA *pp = dynamic_cast<SquareAA*>(p))
		return hit(*pp);
	else
		return INF;
}

double RayCast::hit(const Plane &pi)
{
	double t0 = dotProduct(pi.n, pi.p - r.a);
	double t1 = dotProduct(r.b, pi.n);

	if(abs(t0) <= EPS && abs(t1) <= EPS)
		return 0;
	else if(abs(t1) <= EPS || (t0 / t1) < 0)
		return INF;
	else
		return t0 / t1;
}

double RayCast::hit(const Triangle &t)
{
	double d = hit(Plane(t));

	if(d == INF)
		return INF;
	if(t.containsPointInPlane(Vector(r.a + d * r.b)))
		return d;
	return INF;
}

double RayCast::hit(const SquareAA &sq)
{
	double d = hit(Plane(sq));

	if(d == INF)
		return INF;
	if(sq.containsPointInPlane(Vector(r.a + d * r.b)))
		return d;
	return INF;
}
