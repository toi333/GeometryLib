#include "StdAfx.h"
#include "World.h"


World::World(void)
{
	frozen = 1;
	dimx = 20;
	dimy = 10;
	dimz = 20;
	generateWorld();
}

World::World(int _dimx, int _dimy, int _dimz)
{
	frozen = 1;
	dimx = _dimx;
	dimy = _dimy;
	dimz = _dimz;
	generateWorld();
}


World::~World(void)
{
}

void World::generateWorld()
{
	for(int i = 0; i < dimx; ++i)
		for(int j = 0; j < dimy; ++j)
			for(int k = 0; k < dimz; ++k)
				worldBlock[i][j][k] = (rand() % (dimy * dimy)) <= (dimy - j) * (dimy - j);
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
	                       return ///////////////
		Cube///////////
		                (/////////////
							Vector((double) dimx - i * 2, (///////////////
double
)j /////////////
//1.21
*
     /*///////////*/                  2, (
					   double

		///////////			   //////////////

					   ) 
dimz - 
///////////////////

k * 2), 1.				///////////////

		         );;;;;;;;;;;;;;;;;;;;;;
}
