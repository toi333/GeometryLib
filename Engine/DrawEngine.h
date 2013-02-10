#pragma once

#include <math.h>
#include "GeometryLib.h"
#include "World.h"
#include "TextObject.h"
#include <list>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/freeglut.h>
#else
#include <GL/freeglut.h>
#endif

class DrawEngine
{
public:
	std::list<PointSet*> PSBuffer;
	std::list<TextObject*> textBuffer;

	DrawEngine();
	~DrawEngine();

	void draw(PointSet *a);
	void draw(const World &a);
	void draw(const WorldChunk &a);
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

	void addToTextBuffer(TextObject *a);
	void drawTextBuffer(int w, int h);
	void drawText(TextObject *t);
};
