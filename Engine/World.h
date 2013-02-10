#pragma once

#include "Primitives.h"
#include "WorldChunk.h"
#include "PhysicsObjects.h"

class World : 
	public PhysicsObject, public PointSet
{
public:
	World(void);
	World(int _dimx, int _dimy);
	~World(void);

	void generateWorld();
	void generateList();

	Vector getPos() const;
	void setPos(const Vector &_v);
	void update(double dt);

	bool existsAtIdx(int i, int j, int k) const;
	bool isValidIdx(int i, int j) const;
	Cube getBlockAtIdx(int i, int j, int k) const;
	WorldChunk* getChunkAtIdx(int i, int j) const;

	Box getAABB();

	int dimx, dimy;
	WorldChunk *worldChunk[16][16];
	int blockCount;

private:
	void f(int x1, int x2, int z1, int z2, int h = 1);
};
