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

PointSet* Intersection::get()
{
	return p;
}

void Intersection::intersect(const Ray &r, PointSet *ps)
{
	if(Triangle *pp = dynamic_cast<Triangle*>(ps))
		intersect(r, *pp);
	else if(Plane *pp = dynamic_cast<Plane*>(ps))
		intersect(r, *pp);
	else if(Vector *pp = dynamic_cast<Vector*>(ps))
		intersect(r, *pp);
	else if(EmptyPS *pp = dynamic_cast<EmptyPS*>(ps))
		intersect(r, *pp);
	else
	{
		clear();
		p = new EmptyPS(); 
	}
}

void Intersection::intersect(const Ray &r, const Plane &pi)
{
	clear();

	double t0 = dotProduct(pi.n, pi.p - r.a);
	double t1 = dotProduct(r.b, pi.n);

	if(abs(t0) <= EPS && abs(t1) <= EPS)
		p = new Ray(r);
	else if(abs(t1) <= EPS || (t0 / t1) < 0)
		p = new EmptyPS();
	else
		p = new Vertex((t0 / t1) * r.b + r.a);
}

void Intersection::intersect(const Ray &r, const Triangle &t)
{
	intersect(r, Plane(t));
	if(typeid(*p) == typeid(EmptyPS))
		return;
	else if(typeid(*p) == typeid(Ray))
	{
		//TODO: finish
	}
	else if(!t.containsPointInPlane(Vector(*(Vector*)p)))
	{
		clear();
		p = new EmptyPS();
	}
}

void Intersection::intersect(const Ray &r, const Vector &v)
{
	intersect(v, r);
}

void Intersection::intersect(const Line &l, const Triangle &t)
{
	intersect(l, Plane(t));
	if(typeid(*p) == typeid(EmptyPS))
		return;
	else if(typeid(*p) == typeid(Line))
	{
		//TODO: finish
	}
	else if(!t.containsPointInPlane(Vector(*(Vector*)p)))
	{
		clear();
		p = new EmptyPS();
	}
}

void Intersection::intersect(const Line &l, const Plane &pi)
{
	clear();

	double t0 = dotProduct(pi.n, pi.p - l.a);
	double t1 = dotProduct(l.b, pi.n);

	if(abs(t0) <= EPS && abs(t1) <= EPS)
		p = new Line(l);
	else if(abs(t1) <= EPS)
		p = new EmptyPS();
	else
		p = new Vertex((t0 / t1) * l.b + l.a);
}

void Intersection::intersect(const Vector &v, const Plane &pi)
{
	clear();

	if(pi.containsPoint(v))
		p = new Vertex(v);
	else
		p = new EmptyPS();
}

void Intersection::intersect(const Vector &v, const Triangle &t)
{
	clear();

	if(t.containsPoint(v))
		p = new Vertex(v);
	else
		p = new EmptyPS();
}

void Intersection::intersect(const Vector &v, const Segment &s)
{
	clear();

	double t;
	if(abs(s.b.x - s.a.x) >= EPS)
		t = (s.a.x - v.x) / (s.a.x - s.b.x);
	else if(abs(s.b.y - s.a.y) >= EPS)
		t = (s.a.y - v.y) / (s.a.y - s.b.y);
	else
		t = (s.a.z - v.z) / (s.a.z - s.b.z);

	intersect(v, Line(s)); //TODO: zamjeni s provjerom
	if(typeid(*p) == typeid(EmptyPS))
		return;
	else if(t <= 1. && t >= 0.)
		p = new Vertex(v);
	else
		p = new EmptyPS();
}

void Intersection::intersect(const Vector &v, const Ray &r)
{
	clear();

	double a = (v.x - r.a.x) / r.b.x;
	double b = (v.y - r.a.y) / r.b.y;
	double c = (v.z - r.a.z) / r.b.z;

	if     (abs(r.b.x) < EPS && abs(r.b.y) < EPS)
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
		p = new Vertex(v);
	else
		p = new EmptyPS();
}

void Intersection::intersect(const Vector &v, const Line &l)
{
	clear();
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
		p = new Vertex(v);
	else
		p = new EmptyPS();
}

void Intersection::intersect(const Vector &v, const Vector &u)
{
	clear();
	if(abs(v.x) - abs(u.x) < EPS && abs(v.y) - abs(u.y) < EPS && abs(v.z) - abs(u.z) < EPS)
		p = new Vertex(v);
	else
		p = new EmptyPS();
}

#pragma region EmptyPS intersections

void Intersection::intersect(const Vector &v, const EmptyPS &e)
{
	clear();
	p = new EmptyPS();
}

void Intersection::intersect(const EmptyPS &e, const EmptyPS &f)
{
	clear();
	p = new EmptyPS();
}

void Intersection::intersect(const EmptyPS &e, const Triangle &t)
{
	clear();
	p = new EmptyPS();
}

void Intersection::intersect(const EmptyPS &e, const Plane &pi)
{
	clear();
	p = new EmptyPS();
}

void Intersection::intersect(const EmptyPS &e, const Line &l)
{
	clear();
	p = new EmptyPS();
}

void Intersection::intersect(const EmptyPS &e, const Segment &s)
{
	clear();
	p = new EmptyPS();
}

void Intersection::intersect(const EmptyPS &e, const Ray &r)
{
	clear();
	p = new EmptyPS();
}
void Intersection::intersect(const EmptyPS &e, const Vector &v)
{
	clear();
	p = new EmptyPS();
}

void Intersection::intersect(const Ray &r, const EmptyPS &e)
{
	clear();
	p = new EmptyPS();
}

void Intersection::clear()
{
	if(p)
		delete p;
}

#pragma endregion
