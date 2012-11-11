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
};
