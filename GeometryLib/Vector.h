#pragma once

#include "PointSet.h"
#include "Essential.h"

class Vector :
	public PointSet
{
public:
	double x, y, z;

	Vector(void);
	Vector(double _x, double _y, double _z);
	~Vector(void);

	Vector operator+(const Vector &v) const;
	Vector operator-(const Vector &v) const;
	Vector operator*(double t) const;
	Vector operator/(double t) const;

	Vector operator+=(const Vector &v);
	Vector operator-=(const Vector &v);
	Vector operator*=(double t);
	Vector operator/=(double t);
	
	bool operator<(const Vector &v) const;
	bool operator>(const Vector &v) const;
	bool operator<=(const Vector &v) const;
	bool operator>=(const Vector &v) const;

	Vector operator-(void) const;
	double length(void) const;
	double length2(void) const;
	
	double distance(const Vector &v) const;
	double distance2(const Vector &v) const;

	Vector normalized(void) const;
	Vector normalize(void);

};

double dotProduct(const Vector &a, const Vector &b);
Vector crossProduct(const Vector &a, const Vector &b);
double mixedProduct(const Vector &a, const Vector &b, const Vector &c);

Vector operator*(double t, const Vector &v);
