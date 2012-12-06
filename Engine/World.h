#pragma once

#include "Primitives.h"
#include "PhysicsObjects.h"
#include <list>

class World
{
public:
	World(void);
	World(int dim);
	~World(void);

	void generateWorld(int dim);

	int objCount;
	CubePH *worldBlock[100000];
};

