#pragma once

#include "PointSet.h"

class EmptyPS :
	public PointSet
{
public:
	EmptyPS(void);
	~EmptyPS(void);

	Vector getPos() const;
	void setPos(const Vector &_v);

private:
};

