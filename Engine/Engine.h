#pragma once

#include "DrawEngine.h"
#include "GeometryLib.h"
#include "Player.h"
#include "PhysicsProcessor.h"
#include "World.h"

#include <windows.h>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


namespace Engine
{
	extern DrawEngine de;
	extern Player c;
	extern PhysicsProcessor PP;
	extern World w;

	void start(int argc, char **argv);
	void initWorld();
	void nextFrame();
	void handleResize(int w, int h);
	void idle(void);
	void initRendering(int argc, char **argv);

	void handleKeyDown(unsigned char key, int x, int y);
	void handleKeyUp(unsigned char key, int x, int y);
	void handleMouseMove(int x, int y);
	void mouseFunc(int button, int state, int x, int y);

	void fireRay(const Ray &r, int maxBounces = 100);
}
