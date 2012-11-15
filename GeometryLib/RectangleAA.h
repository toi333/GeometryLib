#pragma once

#include "Surface.h"

enum AxisDirection;

class RectangleAA :
	public Surface
{
public:
	Vector a, d;
	AxisDirection dir;

	RectangleAA(void);
	RectangleAA(const Vector &_a, const Vector &_d, AxisDirection _dir);
	~RectangleAA(void);

	Vector normal() const;
	Vector getVertex(int index) const;
	bool containsPoint(const Vector &v) const;
	bool containsPointInPlane(const Vector &v) const;

	Vector pos() const;

private:
	static const Vector normals[6];
	static const Vector vertices[6][4];
};
