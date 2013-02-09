#include "StdAfx.h"
#include "World.h"
#include <cstring>

World::World(void)
{
	memset(qacnt, 0, sizeof qacnt);
	memset(quadArray, 0, sizeof quadArray);
	blockCount = 0;
	frozen = 1;
	dimx = 50;
	dimy = 20;
	dimz = 50;
	//generateWorld();
}

World::World(int _dimx, int _dimy, int _dimz)
{
	memset(qacnt, 0, sizeof qacnt);
	memset(quadArray, 0, sizeof quadArray);
	blockCount = 0;
	frozen = 1;
	dimx = _dimx;
	dimy = _dimy;
	dimz = _dimz;
	//generateWorld();
}


World::~World(void)
{
	for(int i = 0; i < 6; ++i)
		delete [] quadArray[i];
}

void World::generateWorld()
{
	blockCount = 0;
	for(int i = 0; i < dimx; ++i)
		for(int j = 0; j < dimy; ++j)
			for(int k = 0; k < dimz; ++k)
			{
				worldBlock[i][j][k] = (rand() % (dimy * dimy)) <= (dimy - j) * (dimy - j);
				++blockCount;
			}

	generateList();
}

void World::generateList()
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
				if(worldBlock[i][j][k])
				{
					Cube cb = getBlockAtIdx(i, j, k);
					for(int d = 0; d < 6; ++d)
					{
						int ni = i + dx[d];
						int nj = j + dy[d];
						int nk = k + dz[d];
						if(!isValidIdx(ni, nj, nk) || !worldBlock[ni][nj][nk])
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

bool World::isValidIdx(int i, int j, int k) const
{
	return i >= 0 && j >= 0 && k >= 0 && i < dimx && j < dimy && k < dimz;
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
	return Box(Vector(0., dimy, 0.), Vector(dimx, dimy, dimz));
}

Cube World::getBlockAtIdx(int i, int j, int k) const
{
	return Cube(Vector(i * 2 - dimx, j * 2, k * 2 - dimz), 1.);
}

/* //funkcija krivo vraca... da nije bilo ovog sranja ustedili bi koji sat
Cube World::getBlockAtIdx(int i, int j, int k) const
{
	                       return ///////////////
		Cube///////////
		                (/////////////
							Vector((double) dimx - i * 2, (///////////////
double
)j /////////////
//1.21
*
                       2, (
					   double

		///////////			   //////////////

					   ) 
dimz - 
///////////////////

k * 2), 1.				///////////////

		         );;;;;;;;;;;;;;;;;;;;;;
}
*/