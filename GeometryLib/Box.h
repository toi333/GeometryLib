#pragma once

#include "VolumetricObject.h"
#include "RectangleAA.h"

class Box :
	public VolumetricObject
{
public:
	Vector a, d;

	Box(void);
	Box(const Vector &_a, const Vector &_d);
	virtual ~Box(void);

	Vector getVertex(int index) const;
	Vector getNormal(int index) const;
	RectangleAA getSide(int index) const;

	virtual Vector getPos() const;
	virtual void setPos(const Vector &_v);
	double volume() const;

	std::pair<double, Vector> reflect(const Ray &r) const;

private:
	static const Vector normals[6];
	static const Vector vertices[8];
};

