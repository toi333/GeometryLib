#include "StdAfx.h"
#include "RayCast.h"

using namespace std;

RayCast::RayCast(void)
{
}

RayCast::RayCast(const Ray &r)
{
	a = r.a;
	b = r.b;
}

RayCast::~RayCast(void)
{
}


double RayCast::hit(const Plane &pi)
{
	double t0 = dotProduct(pi.n, pi.p - a);
	double t1 = dotProduct(b, pi.n);

	if(abs(t0) <= EPS && abs(t1) <= EPS)
		return 0;
	else if(abs(t1) <= EPS || (t0 / t1) < 0)
		return INF;
	else
		return t0 / t1;
}

double RayCast::hit(const Triangle &t)
{
	Plane pi(t);
	double t0 = dotProduct(pi.n, pi.p - a);
	double t1 = dotProduct(b, pi.n);

	if(abs(t0) <= EPS && abs(t1) <= EPS)
		return INF; //HACK: sredi
	else if(abs(t1) <= EPS || (t0 / t1) < 0)
		return INF;
	else
	{
		Vector v(t0 / t1 * b + a);
		double a = sgn(t.ccw(crossProduct(t.a - t.c, v - t.c)));
		double b = sgn(t.ccw(crossProduct(t.b - t.a, v - t.a)));
		double c = sgn(t.ccw(crossProduct(t.c - t.b, v - t.b)));
		if(min(a, b, c) == -max(a, b, c))
			return INF;
		return t0 / t1;
	}
}

double RayCast::hit(PointSet *p)
{
	switch(p->type())
	{
	case PLANE:
		return hit(*(Plane*)p);
		break;
	case TRIANGLE:
		return hit(*(Triangle*)p);
		break;
	default:
		return INF;
		break;
	}
}


void RayCast::cast(int maxBounces)
{
	if(maxBounces < 0)
		return;
	double mn = INF;
	PointSet *p = NULL;
	for(list<PointSet*>::const_iterator it = getBuffer().begin(); it != getBuffer().end(); ++it)
			if((*it)->type() == PLANE || (*it)->type() == TRIANGLE)
			{
				double a = hit(*it);
				if(a < mn && a > EPS)
				{
					p = *it;
					mn = a;
				}
			}
	if(mn != INF)
	{
		Vector n;
		Vector x(a + b * mn);
		if(p->type() == PLANE)
			n = ((Plane*)p)->n;
		else
			n = ((Triangle*)p)->normal();
		addToBuffer(new Segment(a, x));
		RayCast(Ray(x, b - 2 * dotProduct(n, b) * n + x)).cast(--maxBounces);
	}
	else
		addToBuffer(new Ray((Ray)*this));
}
