#pragma once

#include "Surface.h"
#include "Triangle.h"
#include "SquareAA.h"

class Plane :
	public Surface
{
public:
	Vector p, n;

	Plane(void);
	Plane(const Vector &_p, const Vector &_n);
	Plane(const Vector &a, const Vector &b, const Vector &c);
	Plane(const Triangle &tri);
	Plane(const SquareAA &sq);
	~Plane(void);
	
	Vector normal() const;
	double a() const;
	double b() const;
	double c() const;
	double d() const;

	bool containsPoint(const Vector &v) const;
	bool containsPointInPlane(const Vector &v) const;

};

