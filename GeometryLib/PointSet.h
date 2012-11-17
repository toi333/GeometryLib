#pragma once

#include "Vector.h"

class Vector;

class PointSet
{
public:
	PointSet(void);
	virtual ~PointSet(void);

	virtual Vector getPos() const = 0;
	virtual void setPos(const Vector &_v) = 0;
private:
};
