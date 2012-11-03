#pragma once

#include "PointSet.h"
#include "Vector.h"

class Surface :
	public PointSet
{
public:
	virtual Vector normal() const;

	Surface(void);
	~Surface(void);
};

