#pragma once

#include "PointSet.h"
#include "Vertex.h"

class Surface :
	public PointSet
{
public:
	Vector p;

	Surface(void);
	virtual ~Surface(void);

	virtual Vector normal() const = 0;
	//virtual Vector getPos() const = 0;

	virtual bool containsPoint(const Vector &v) const = 0;
	virtual bool containsPointInPlane(const Vector &v) const = 0;
};
