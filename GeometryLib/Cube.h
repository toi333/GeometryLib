#pragma once

#include "VolumetricObject.h"
#include "SquareAA.h"

class Cube :
	public VolumetricObject
{
public:
	Vector a;
	double d;

	Cube(void);
	Cube(const Vector &_a, double _d);
	virtual ~Cube(void);

	Vector getVertex(int index) const;
	Vector getNormal(int index) const;
	SquareAA getSide(int index) const;

	Vector pos() const;
	double volume() const;

	std::pair<double, Vector> reflect(const Ray &r) const;

private:
	static const Vector normals[6];
	static const Vector vertices[8];
};
