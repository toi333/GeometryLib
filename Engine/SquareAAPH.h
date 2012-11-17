#pragma once

#include "SquareAA.h" 
#include "PhysicsObject.h"

class SquareAAPH :
	public SquareAA, public PhysicsObject
{
public:
	SquareAAPH(void);
	SquareAAPH(const SquareAA &sq);
	SquareAAPH(const SquareAA &sq, const Vector &_vel);
	SquareAAPH(const SquareAA &sq, const Vector &_vel, double _mass, bool _frozen);
	~SquareAAPH(void);

	Vector getPos() const;
	void setPos(const Vector &_v);

	void update( double dt );
};

