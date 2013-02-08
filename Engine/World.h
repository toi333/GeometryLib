#pragma once

#include "Primitives.h"
#include "PhysicsObjects.h"
#include <list>

class World : public PhysicsObject, public PointSet
{
public:
	World(void);
	World(int _dimx, int _dimy, int _dimz);
	~World(void);

	void generateWorld();

	Vector getPos() const;
	void setPos(const Vector &_v);
	void update(double dt);

	Cube getBlockAtIdx(int i, int j, int k) const;
	Box getAABB();

	int dimx, dimy, dimz;
	bool worldBlock[100][20][100];
	double *quadArray;
	int qacnt;
};

