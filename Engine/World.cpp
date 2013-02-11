#include "StdAfx.h"
#include "World.h"
#include <cstring>

World::World(void)
{
	blockCount = 0;
	frozen = 1;
	dimx = 8;
	dimy = 8;
	for(int i = 0; i < dimx; ++i)
		for(int j = 0; j < dimy; ++j)
		{
			worldChunk[i][j] = new WorldChunk(
				Vector((2 * i + 1 - dimx) * WorldChunk::dimx, 0, (2 * j + 1 - dimy) * WorldChunk::dimz));
		}
}

World::World(int _dimx, int _dimy)
{
	blockCount = 0;
	frozen = 1;
	dimx = _dimx;
	dimy = _dimy;
	for(int i = 0; i < dimx; ++i)
		for(int j = 0; j < dimy; ++j)
		{
			worldChunk[i][j] = new WorldChunk(
				Vector((2 * i + 1 - dimx) * WorldChunk::dimx, 0, (2 * j + 1 - dimy) * WorldChunk::dimz));
		}
}


World::~World(void)
{
	for(int i = 0; i < dimx; ++i)
		for(int j = 0; j < dimy; ++j)
			delete worldChunk[i][j];
}

void World::generateWorld()
{
	//for(int i = 0; i < dimx; ++i)
	//	for(int j = 0; j < dimy; ++j)
	//	{
	//		worldChunk[i][j]->generateChunk();
	//		blockCount += worldChunk[i][j]->blockCount;
	//	}
	//	generateList();

	for(int i = 0; i < dimx; ++i)
		for(int j = 0; j < dimy; ++j)
			worldChunk[i][j]->blockCount = 0;
	f(0, dimx * WorldChunk::dimx - 1, 0, dimy * WorldChunk::dimz - 1, 1);
	blockCount = 0;
	for(int i = 0; i < dimx; ++i)
		for(int j = 0; j < dimy; ++j)
			blockCount += worldChunk[i][j]->blockCount;
	generateList();
}

void World::generateList()
{
	for(int i = 0; i < dimx; ++i)
		for(int j = 0; j < dimy; ++j)
			worldChunk[i][j]->generateList();
}

bool World::isValidIdx(int i, int j) const
{
	return i >= 0 && j >= 0 && i < dimx && j < dimy;
}

Vector World::getPos() const
{
	return Vector();
}

void World::setPos(const Vector &_v)
{
}

void World::update(double dt)
{
}

Box World::getAABB()
{
	return Box(Vector(0., WorldChunk::dimy, 0.), 
		Vector(dimx * WorldChunk::dimx, WorldChunk::dimy, dimy * WorldChunk::dimz));
}

Cube World::getBlockAtIdx(int i, int j, int k) const
{
	return Cube(Vector(i * 2 - dimx * WorldChunk::dimx, j * 2, k * 2 - dimy * WorldChunk::dimz), 1.);
}

WorldChunk* World::getChunkAtIdx(int i, int j) const
{
	return worldChunk[i][j];
}

bool World::existsAtIdx(int i, int j, int k) const
{
	return worldChunk[i/WorldChunk::dimx][k/WorldChunk::dimz]->
		chunkBlock[i%WorldChunk::dimx][j][k%WorldChunk::dimz];
}

void World::f(int x1, int x2, int z1, int z2, int h)
{
	if(x1 > x2 || z1 > z2)
		return;
	if(x1 == x2 && z1 == z2)
	{
		for(int i = 0; i < h; ++i)
			worldChunk[x1/WorldChunk::dimx][z1/WorldChunk::dimz]->
			chunkBlock[x1%WorldChunk::dimx][i][z1%WorldChunk::dimz] = 1;
		worldChunk[x1/WorldChunk::dimx][z1/WorldChunk::dimz]->blockCount += h;
		return;
	}

	f(x1, (x2 + x1) / 2, z1, (z1 + z2) / 2, h + rand() % 2);
	f((x2 + x1) / 2 + 1, x2, z1, (z1 + z2) / 2, h + rand() % 2);
	f(x1, (x2 + x1) / 2, (z1 + z2) / 2 + 1, z2, h + rand() % 2);
	f((x2 + x1) / 2 + 1, x2,  (z1 + z2) / 2 + 1, z2, h + rand() % 2);
}
