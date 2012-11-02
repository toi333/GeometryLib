#pragma once

#include "Primitives.h"
#include "Essential.h"

class Intersection
{
private:
	PointSet *p;
public:
	Intersection(void);
	~Intersection(void);

	void intersect(const Ray &r, PointSet *ps);

	void intersect(const Vector &v, const Triangle &t);
	void intersect(const Vector &v, const Plane &pi);
	void intersect(const Vector &v, const Segment &s);
	void intersect(const Vector &v, const Ray &r);
	void intersect(const Vector &v, const Line &l);
	void intersect(const Vector &v, const Vector &u);
	void intersect(const Vector &v, const EmptyPS &e);

	void intersect(const EmptyPS &e, const EmptyPS &f);
	void intersect(const EmptyPS &e, const Triangle &t);
	void intersect(const EmptyPS &e, const Plane &pi);
	void intersect(const EmptyPS &e, const Line &l);
	void intersect(const EmptyPS &e, const Segment &s);
	void intersect(const EmptyPS &e, const Ray &r);
	void intersect(const EmptyPS &e, const Vector &v);

	void intersect(const Ray &r, const Plane &pi);
	void intersect(const Ray &r, const Triangle &t);
	void intersect(const Ray &r, const Vector &v);
	void intersect(const Ray &r, const EmptyPS &e);

	void intersect(const Line &l, const Plane &pi);
	void intersect(const Line &l, const Triangle &t);


	PointSet *get();
};
