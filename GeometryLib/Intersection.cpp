#include "StdAfx.h"
#include "Intersection.h"

Intersection::Intersection(void)
{
	p = NULL;
}

Intersection::~Intersection(void)
{
	delete p;
}

void Intersection::intersect(const Line &l, const Triangle &t)
{
	intersect(l, Plane(t));
	if(p->type() == EMPTYPS)
		return;
	else if(p->type() == LINE)
	{
		//TODO: finish
	}
	else
	{
		Vector v(*(Vector*)p);
		double a = sgn(t.ccw(crossProduct(t.a - t.c, v - t.c)));
		double b = sgn(t.ccw(crossProduct(t.b - t.a, v - t.a)));
		double c = sgn(t.ccw(crossProduct(t.c - t.b, v - t.b)));
		if(min(a, b, c) == -max(a, b, c))
		{
			if(p)
				delete p;
			p = new EmptyPS();
		}
	}
}

void Intersection::intersect(const Line &l, const Plane &pi)
{
	if(p)
		delete p;

	double t0 = dotProduct(pi.n, pi.p - l.a);
	double t1 = dotProduct(l.b, pi.n);

	if(abs(t0) <= EPS && abs(t1) <= EPS)
		p = new Line(l);
	else if(abs(t1) <= EPS)
		p = new EmptyPS();
	else
		p = new Vector((t0 / t1) * l.b + l.a);
}

PointSet* Intersection::get()
{
	return p;
}

void Intersection::intersect(const Ray &r, const Plane &pi)
{
	if(p)
		delete p;

	double t0 = dotProduct(pi.n, pi.p - r.a);
	double t1 = dotProduct(r.b, pi.n);

	if(abs(t0) <= EPS && abs(t1) <= EPS)
		p = new Ray(r);
	else if(abs(t1) <= EPS || (t0 / t1) < 0)
		p = new EmptyPS();
	else
		p = new Vector((t0 / t1) * r.b + r.a);
}

void Intersection::intersect(const Ray &r, const Triangle &t)
{
	intersect(r, Plane(t));
	if(p->type() == EMPTYPS)
		return;
	else if(p->type() == LINE)
	{
		//TODO: finish
	}
	else
	{
		Vector v(*(Vector*)p);
		double a = sgn(t.ccw(crossProduct(t.a - t.c, v - t.c)));
		double b = sgn(t.ccw(crossProduct(t.b - t.a, v - t.a)));
		double c = sgn(t.ccw(crossProduct(t.c - t.b, v - t.b)));
		if(min(a, b, c) == -max(a, b, c))
		{
			if(p)
				delete p;
			p = new EmptyPS();
		}
	}
}


void Intersection::intersect(const Vector &v, const Plane &pi)
{
	if(p)
		delete p;
	if(abs(dotProduct(v - pi.p, pi.n)) <= EPS)
		p = new Vector(v);
	else
		p = new EmptyPS();
}

void Intersection::intersect(const Vector &v, const Triangle &t)
{
	if(p)
		delete p;
	Plane pi(t);
	if(abs(dotProduct(v - pi.p, pi.n)) <= EPS)
	{
		double a = sgn(t.ccw(crossProduct(t.a - t.c, v - t.c)));
		double b = sgn(t.ccw(crossProduct(t.b - t.a, v - t.a)));
		double c = sgn(t.ccw(crossProduct(t.c - t.b, v - t.b)));
		if(min(a, b, c) != -max(a, b, c))
			p = new Vector(v);
		else
			p = new EmptyPS();
	}
	else
		p = new EmptyPS();
}

void Intersection::intersect(const Vector &v, const Segment &s)
{
	if(p)
		delete p;

	double t;
	if(abs(s.b.x - s.a.x) >= EPS)
		t = (s.a.x - v.x) / (s.a.x - s.b.x);
	else if(abs(s.b.y - s.a.y) >= EPS)
		t = (s.a.y - v.y) / (s.a.y - s.b.y);
	else
		t = (s.a.z - v.z) / (s.a.z - s.b.z);

	printf("%.2lf\n", t);

	intersect(v, Line(s)); //TODO: zamjeni s provjerom
	if(p->type() == EMPTYPS)
		return;
	else if(t <= 1. && t >= 0.)
		p = new Vector(v);
	else
		p = new EmptyPS();
}

void Intersection::intersect(const Vector &v, const Ray &r)
{
	if(p)
		delete p;
	double a = (v.x - r.a.x) / r.b.x;
	double b = (v.y - r.a.y) / r.b.y;
	double c = (v.z - r.a.z) / r.b.z;

	if(abs(r.b.x) < EPS && abs(r.b.y) < EPS)
		a = b = c;
	else if(abs(r.b.x) < EPS && abs(r.b.z) < EPS)
		a = c = b;
	else if(abs(r.b.y) < EPS && abs(r.b.z) < EPS)
		b = c = a;
	else if(abs(r.b.x) < EPS)
		a = b;
	else if(abs(r.b.y) < EPS)
		b = a;
	else if(abs(r.b.z) < EPS)
		c = a;

	if(max(a, b, c) - min(a, b, c) < EPS && a >= 0.)
		p = new Vector(v);
	else
		p = new EmptyPS();
}

void Intersection::intersect(const Vector &v, const Line &l)
{
	if(p)
		delete p;
	double a = (v.x - l.a.x) / l.b.x;
	double b = (v.y - l.a.y) / l.b.y;
	double c = (v.z - l.a.z) / l.b.z;

	if(abs(l.b.x) < EPS && abs(l.b.y) < EPS)
		a = b = c;
	else if(abs(l.b.x) < EPS && abs(l.b.z) < EPS)
		a = c = b;
	else if(abs(l.b.y) < EPS && abs(l.b.z) < EPS)
		b = c = a;
	else if(abs(l.b.x) < EPS)
		a = b;
	else if(abs(l.b.y) < EPS)
		b = a;
	else if(abs(l.b.z) < EPS)
		c = a;

	if(max(a, b, c) - min(a, b, c) <= EPS)
		p = new Vector(v);
	else
		p = new EmptyPS();
}

void Intersection::intersect(const Vector &v, const Vector &u)
{
	if(p)
		delete p;
	if(abs(v.x) - abs(u.x) < EPS && abs(v.y) - abs(u.y) < EPS && abs(v.z) - abs(u.z) < EPS)
		p = new Vector(v);
	else
		p = new EmptyPS();
}

void Intersection::intersect(const Vector &v, const EmptyPS &e)
{
	if(p)
		delete p;
	p = new EmptyPS();
}

void Intersection::intersect(const EmptyPS &e, const EmptyPS &f)
{
	if(p)
		delete p;
	p = new EmptyPS();
}

void Intersection::intersect(const EmptyPS &e, const Triangle &t)
{
	if(p)
		delete p;
	p = new EmptyPS();
}

void Intersection::intersect(const EmptyPS &e, const Plane &pi)
{
	if(p)
		delete p;
	p = new EmptyPS();
}

void Intersection::intersect(const EmptyPS &e, const Line &l)
{
	if(p)
		delete p;
	p = new EmptyPS();
}

void Intersection::intersect(const EmptyPS &e, const Segment &s)
{
	if(p)
		delete p;
	p = new EmptyPS();
}

void Intersection::intersect(const EmptyPS &e, const Ray &r)
{
	if(p)
		delete p;
	p = new EmptyPS();
}
