#pragma once

#include "PointSet.h"
#include "Triangle.h"
#include "Vector.h"

class Plane :
	public PointSet
{
public:
	Plane(void);
	Plane(const Vector &_p, const Vector &_n);
	Plane(const Vector &a, const Vector &b, const Vector &c);
	Plane(const Triangle &tri);
	~Plane(void);
	
	double a() const;
	double b() const;
	double c() const;
	double d() const;
	PSType type();

	Vector p, n;
private:
};

