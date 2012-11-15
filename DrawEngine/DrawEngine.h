#pragma once

#include <math.h>
#include "GeometryLib.h"
#include <list>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class DrawEngine
{
public:
	std::list<PointSet*> PSBuffer; 

	DrawEngine();
	~DrawEngine();

	void draw(PointSet *a);
	void draw(const Cube &a);
	void draw(const Box &a);
	void draw(const SquareAA &a);
	void draw(const RectangleAA &a);
	void draw(const Vector &a);
	void draw(const Line &a);
	void draw(const Ray &a);
	void draw(const Segment &a);
	void draw(const Triangle &a);
	void draw(const Plane &a);
	void draw(const EmptyPS &a);
	void draw(const PointSet &a);

	void addToBuffer(PointSet *a);
	void drawBuffer();
};