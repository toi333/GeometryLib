#pragma once

#include "PointSet.h"
#include "Vector.h"

class Surface :
	public PointSet
{
public:
	Surface(void);
	virtual ~Surface(void);

	virtual Vector normal() const = 0;

	virtual bool containsPoint(const Vector &v) const = 0;
	virtual bool containsPointInPlane(const Vector &v) const = 0;
};
