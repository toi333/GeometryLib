#pragma once

#include "Surface.h"
#include "Triangle.h"

class Plane :
	public Surface
{
public:
	Plane(void);
	Plane(const Vector &_p, const Vector &_n);
	Plane(const Vector &a, const Vector &b, const Vector &c);
	Plane(const Triangle &tri);
	~Plane(void);
	
	Vector normal() const;
	double a() const;
	double b() const;
	double c() const;
	double d() const;
	PSType type() const;

	Vector p, n;
private:
};

