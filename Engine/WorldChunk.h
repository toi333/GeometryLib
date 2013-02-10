#pragma once

#include "Primitives.h"
#include "PhysicsObjects.h"

class WorldChunk :
	public PhysicsObject, public PointSet
{
public:
	WorldChunk(void);
	WorldChunk(const Vector &_p);
	~WorldChunk(void);

	void generateChunk();
	void generateList();

	Vector getPos() const;
	void setPos(const Vector &_v);
	void update(double dt);

	bool isValidIdx(int i, int j, int k) const;
	Cube getBlockAtIdx(int i, int j, int k) const;
	Box getAABB();

	static const int dimx = 16, dimy = 32, dimz = 16;
	Vector p;
	bool chunkBlock[dimx][dimy][dimz];
	int blockCount;
	double *quadArray[6];
	int qacnt[6];
};

