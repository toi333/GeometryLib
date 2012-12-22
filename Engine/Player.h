#pragma once

#include "GeometryLib.h"
#include "Camera.h"
#include "PhysicsObject.h"

class Player
	: public Camera, public PhysicsObject
{
public:
	Player(void);
	~Player(void);

	void jump();

	void update(double dt);
	Vector getPos() const;
	void setPos(const Vector &_v);

	Box getAABB();

	static Vector d;
	static double pmass;
};

