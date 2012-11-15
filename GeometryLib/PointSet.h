#pragma once

#include "Vector.h"

class Vector;

class PointSet
{
public:
	PointSet(void);
	virtual ~PointSet(void);

	virtual Vector pos() const = 0;
private:
};
