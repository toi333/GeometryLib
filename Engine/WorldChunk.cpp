#include "StdAfx.h"
#include "WorldChunk.h"
#include <cstring>

WorldChunk::WorldChunk(void)
{
	p = Vector();
	memset(qacnt, 0, sizeof qacnt);
	memset(quadArray, 0, sizeof quadArray);
	blockCount = 0;
	frozen = 1;
}

WorldChunk::WorldChunk(const Vector &_p)
{
	p = _p;
	memset(qacnt, 0, sizeof qacnt);
	memset(quadArray, 0, sizeof quadArray);
	blockCount = 0;
	frozen = 1;
}


WorldChunk::~WorldChunk(void)
{
	for(int i = 0; i < 6; ++i)
		delete [] quadArray[i];
}

void WorldChunk::generateChunk()
{
	blockCount = 0;
	for(int i = 0; i < dimx; ++i)
		for(int j = 0; j < dimy; ++j)
			for(int k = 0; k < dimz; ++k)
			{
				chunkBlock[i][j][k] = (rand() % (dimy * dimy)) <= (dimy - j) * (dimy - j);
				++blockCount;
			}
}

void WorldChunk::generateList()
{
	static const int dx[] = {1, 0, 0, -1, 0, 0};
	static const int dy[] = {0, 1, 0, 0, -1, 0};
	static const int dz[] = {0, 0, 1, 0, 0, -1};

	for(int i = 0; i < 6; ++i)
	{
		delete [] quadArray[i];
		quadArray[i] = new double[blockCount * 4 * 3];
	}
	for(int i = 0; i < dimx; ++i)
		for(int j = 0; j < dimy; ++j)
			for(int k = 0; k < dimz; ++k)
				if(chunkBlock[i][j][k])
				{
					Cube cb = getBlockAtIdx(i, j, k);
					for(int d = 0; d < 6; ++d)
					{
						int ni = i + dx[d];
						int nj = j + dy[d];
						int nk = k + dz[d];
						if(!isValidIdx(ni, nj, nk) || !chunkBlock[ni][nj][nk])
						{
							SquareAA sqr = cb.getSide(d);
							for(int l = 0; l < 4; ++l)
							{
								Vector vert = sqr.getVertex(l);
								quadArray[d][qacnt[d]++] = vert.x;
								quadArray[d][qacnt[d]++] = vert.y;
								quadArray[d][qacnt[d]++] = vert.z;
							}
						}
					}
				}
}

bool WorldChunk::isValidIdx(int i, int j, int k) const
{
	return i >= 0 && j >= 0 && k >= 0 && i < dimx && j < dimy && k < dimz;
}

Vector WorldChunk::getPos() const
{
	return p;
}

void WorldChunk::setPos(const Vector &_v)
{
	p = _v;
}

void WorldChunk::update(double dt)
{
}

Box WorldChunk::getAABB()
{
	return Box(Vector(0., dimy, 0.), Vector(dimx, dimy, dimz));
}

Cube WorldChunk::getBlockAtIdx(int i, int j, int k) const
{
	return Cube(Vector(i * 2 - dimx, j * 2, k * 2 - dimz) + p, 1.);
}