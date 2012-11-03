#pragma once

#include "Surface.h"

enum AxisDirection
{
	XP,
	YP,
	ZP,
	XN,
	YN,
	ZN
};

class SquareAA :
	public Surface
{
public:
	Vector a;
	double d;
	AxisDirection dir;

	SquareAA(void);
	SquareAA(const Vector &_a, double _d, AxisDirection _dir);
	~SquareAA(void);

	Vector normal() const;
	Vector getVertex(int index) const;
	PSType type() const;

private:
	static const Vector normals[6];
	static const Vector vertices[6][4];
};

