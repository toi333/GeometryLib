#pragma once

#include "Vector.h"
#include "Player.h"
#include "CubePH.h"
#include "BoxPH.h"
#include "SquareAAPH.h"
#include "PhysicsObject.h"
#include <list>

class PhysicsProcessor
{
public:
	PhysicsProcessor(void);
	~PhysicsProcessor(void);

	void collide(PhysicsObject *a, PhysicsObject *b);
	void collide(CubePH &a, CubePH &b);
	void collide(BoxPH &a, BoxPH &b);
	void collide(BoxPH &a, CubePH &b);
	void collide(CubePH &a, BoxPH &b);
	void collide(CubePH &a, SquareAAPH &b);
	void collide(SquareAAPH &a, CubePH &b);
	void collide(SquareAAPH &b, SquareAAPH &a);
	void collide(Player &b, BoxPH &a);
	void collide(Player &b, CubePH &a);
	void collide(BoxPH &b, Player &a);
	void collide(CubePH &b, Player &a);

	void applyCollision(PhysicsObject &a, PhysicsObject &b, const Vector &n);
	void applyCollisionAA(PhysicsObject &a, PhysicsObject &b, int n, double d);

	std::list<PhysicsObject*> phList;
	void updateList(double dt);
};

