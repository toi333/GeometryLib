#include "StdAfx.h"
#include "Vector.h"

using namespace std;

Vector::Vector(void)
{
	x = y = z = 0.;
}

Vector::Vector(double _x, double _y, double _z)
{
	x = _x;
	y = _y;
	z = _z;
}

Vector::~Vector(void)
{
}

Vector Vector::operator+(const Vector &v) const
{
	return Vector(x + v.x, y + v.y, z + v.z);
}

Vector Vector::operator+=(const Vector &v)
{
	return *this = *this + v;
}

Vector Vector::operator-(const Vector &v) const
{
	return Vector(x - v.x, y - v.y, z - v.z);
}

Vector Vector::operator-=(const Vector &v)
{
	return *this = *this - v;
}

Vector Vector::operator*(double t) const
{
	return Vector(t * x, t * y, t * z);
}

Vector Vector::operator/(double t) const
{
	return Vector(x / t, y / t, z / t);
}

Vector Vector::operator/=(double t)
{
	return *this = *this / t;
}

Vector Vector::operator*=(double t)
{
	return *this = *this * t;
}

bool Vector::operator<(const Vector &v) const
{
	return x < v.x || x == v.x && (y < v.y || y == v.y && z < v.z);
}

bool Vector::operator>(const Vector &v) const
{
	return x > v.x || x == v.x && (y > v.y || y == v.y && z > v.z);
}

bool Vector::operator<=(const Vector &v) const
{
	return !(*this > v);
}

bool Vector::operator>=(const Vector &v) const
{
	return !(*this < v);
}

Vector Vector::operator-(void) const
{
	return Vector(-x, -y, -z);
}

double Vector::length(void) const
{
	return sqrt(length2());
}

double Vector::length2(void) const
{
	return x * x + y * y + z * z;
}
	
double Vector::distance(const Vector &v) const
{
	return (*this - v).length();
}

double Vector::distance2(const Vector &v) const
{
	return (*this - v).length2();
}

Vector Vector::normalized(void) const
{
	if(!x && !y && !z)
		return *this;
	return *this / length();
}

Vector Vector::normalize(void)
{
	if(!x && !y && !z)
		return *this;
	return *this /= length();
}

double dotProduct(const Vector &a, const Vector &b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector crossProduct(const Vector &a, const Vector &b)
{
	return Vector
	(
		a.y * b.z - b.y * a.z,
		b.x * a.z - a.x * b.z,
		a.x * b.y - b.x * a.y
	);
}

Vector pairwiseProduct(const Vector &a, const Vector &b)
{
	return Vector(a.x * b.x, a.y * b.y, a.z * b.z);
}

double mixedProduct(const Vector &a, const Vector &b, const Vector &c)
{
	return dotProduct(a, crossProduct(b, c));
}

Vector operator*(double t, const Vector &v)
{
	return v * t;
}
