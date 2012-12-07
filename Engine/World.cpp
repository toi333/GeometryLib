#include "StdAfx.h"
#include "World.h"


World::World(void)
{
	generateWorld(20);
	objCount = 400;
}

World::World(int dim)
{
	generateWorld(dim);
	objCount = dim * dim;
}


World::~World(void)
{
	for(int i = 0; i < objCount; ++i)
		delete worldBlock[i];
}

void World::generateWorld(int dim)
{
	double height = -10.;
	for(int i = 0; i < dim; ++i)
		for(int j = 0; j < dim; ++j)
		{
			worldBlock[dim * i + j] = new CubePH(Cube(Vector((double) i - (double) dim / 2., height, (double) j - (double) dim / 2.), 1.), 
			Vector(0., 0., 0.), 1., 1);
			//printf("%.2lf, %.2lf, %.2lf\n", (double) i - dim / 2., (double) j - dim / 2., height);
		}
}
