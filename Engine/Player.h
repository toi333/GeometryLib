#pragma once

#include "GeometryLib.h"
#include "Camera.h"
#include "PhysicsObject.h"

class Player
	: public Camera, public PhysicsObject
{
public:
	double d;

	Player(void);
	Player(double _d);
	~Player(void);

	void jump();

	void update(double dt);
	Vector getPos() const;
	void setPos(const Vector &_v);
};

