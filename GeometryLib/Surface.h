#pragma once

#include "PointSet.h"
#include "Vector.h"

class Surface :
	public PointSet
{
public:
	virtual Vector normal() const = 0;

	Surface(void);
	~Surface(void);
};

