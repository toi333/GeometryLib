#include "stdafx.h"
#include "Engine.h"

using namespace std;

int _tmain(int argc,  char **argv)
{
	/*Triangle T(Vector(-3, 0, 3), Vector(3, 0, 0), Vector(-3, 0, -3));
	Cube cb(Vector(0., 0., 0.), 1.);
	SquareAA sq(Vector(), 10., XP);

	addToBuffer(&T);
	addToBuffer(&cb);
	addToBuffer(&sq);
	setCam(c);*/

	Engine::start(argc, argv);
	return 0;
}