#pragma once

#include "GeometryLib.h"
#include "Camera.h"
#include "PhysicsObject.h"

class Player
	: public PhysicsObject, public PointSet
{
public:
	Player(void);
	~Player(void);

	void jump();

	void update(double dt);
	void move(const Vector &_dir);
	Vector getPos() const;
	void setPos(const Vector &_v);

	Box getAABB();

	Camera cam;
	Vector p, dir;
	static Vector d;
	static double pmass;
};

