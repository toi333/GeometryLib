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
	Plane pi(t);
	double t0 = dotProduct(pi.n, pi.p - r.a);
	double t1 = dotProduct(r.b, pi.n);

	if(abs(t0) <= EPS && abs(t1) <= EPS)
		return INF; //HACK: sredi
	else if(abs(t1) <= EPS || (t0 / t1) < 0)
		return INF;
	else
	{
		Vector v(t0 / t1 * r.b + r.a);
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
	case SQUAREAA:
		return hit(*(SquareAA*)p);
		break;
	default:
		return INF;
		break;
	}
}

double RayCast::hit(const SquareAA &sq)
{
	double d = hit(Plane(sq.a, sq.normal()));
	if(d == INF)
		return INF;
	if(sq.dir == XP || sq.dir == XN)
	{
		Vector v(r.a + r.b * d);
		if(sq.a.y - sq.d <= v.y && v.y <= sq.a.y + sq.d &&
			sq.a.z - sq.d <= v.z && v.z <= sq.a.z + sq.d)
			return d;
		return INF;
	}
	if(sq.dir == YP || sq.dir == YN)
	{
		Vector v(r.a + r.b * d);
		if(sq.a.x - sq.d <= v.x && v.x <= sq.a.x + sq.d &&
			sq.a.z - sq.d <= v.z && v.z <= sq.a.z + sq.d)
			return d;
		return INF;
	}
	if(sq.dir == ZP || sq.dir == ZN)
	{
		Vector v(r.a + r.b * d);
		if(sq.a.y - sq.d <= v.y && v.y <= sq.a.y + sq.d &&
			sq.a.x - sq.d <= v.x && v.x <= sq.a.x + sq.d)
			return d;
		return INF;
	}
	return INF;
}

//void RayCast::cast(int maxBounces)
//{
//	if(maxBounces < 0)
//		return;
//	double mn = INF;
//	Vector n;
//	for(list<PointSet*>::const_iterator it = PSBuffer.begin(); it != PSBuffer.end(); ++it)
//	{
//		if((*it)->type() == PLANE || (*it)->type() == TRIANGLE || (*it)->type() == SQUAREAA)
//		{
//			double a = hit(*it);
//			if(a < mn && a > EPS)
//			{
//				n = ((Surface*)*it)->normal();
//				mn = a;
//			}
//		}
//		else if((*it)->type() == CUBE)
//		{	
//			for(int i = 0; i < 6; ++i)
//			{
//				double a = hit(((Cube*)*it)->getSide(i));
//				if(mn > a && a > EPS)
//				{
//					mn = a;
//					n = ((Cube*)*it)->getNormal(i);
//				}
//			}
//		}
//	}
//	if(mn != INF)
//	{
//		Vector x(r.a + r.b * mn);
//		addToBuffer(new Segment(r.a, x));
//		RayCast(Ray(x, r.b - 2 * dotProduct(n, r.b) * n + x)).cast(--maxBounces);
//	}
//	else
//		addToBuffer(new Ray(r));
//}
