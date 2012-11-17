#pragma once

#include "PointSet.h"
#include "Vector.h"

class Vertex :
	public Vector, public PointSet
{
public:
	Vertex(void);
	Vertex(const Vector &v);
	~Vertex(void);

	Vector getPos() const;
	void setPos(const Vector &_v);
};

