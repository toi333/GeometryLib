#include "StdAfx.h"
#include "DrawEngine.h"

using namespace std;

DrawEngine::DrawEngine()
{
}

DrawEngine::~DrawEngine()
{
}

void DrawEngine::draw(const Cube &a)
{	
	if(a.blah)
		glColor3d(0.5, 0.5, 0.7);
	else
		glColor3d(0.0, 0.0, 0.7);

	for(int i = 0; i < 6; ++i)
		draw(a.getSide(i));
	glColor3f(0.5, 0, 0);
}

void DrawEngine::draw(const Box &a)
{
	for(int i = 0; i < 6; ++i)
		draw(a.getSide(i));
}

void DrawEngine::draw(const Vector &a)
{
	glPushMatrix();
		glTranslated(a.x, a.y, a.z);
		glutSolidSphere(.1, 10, 10);
	glPopMatrix();
}

void DrawEngine::draw(const Line &a)
{
	Vector t1 = a.a + a.b * 1000.;
	Vector t2 = a.a - a.b * 1000.;

	glBegin(GL_LINES);
		glVertex3d(t1.x, t1.y, t1.z);
		glVertex3d(t2.x, t2.y, t2.z);
	glEnd();
}

void DrawEngine::draw(const Ray &a)
{
	const Vector &t1 = a.a;
	Vector t2 = a.a + a.b * 1000.;

	glBegin(GL_LINES);
		glVertex3d(t1.x, t1.y, t1.z);
		glVertex3d(t2.x, t2.y, t2.z);
	glEnd();
}

void DrawEngine::draw(const Segment &a)
{
	glBegin(GL_LINES);
		glVertex3d(a.a.x, a.a.y, a.a.z);
		glVertex3d(a.b.x, a.b.y, a.b.z);
	glEnd();
}

void DrawEngine::draw(const Triangle &a)
{
	Vector n(a.normal());
	glBegin(GL_TRIANGLES);
		glColor3f(0., 0.5, 0.);
		glNormal3d(n.x, n.y, n.z);
		glVertex3d(a.a.x, a.a.y, a.a.z);
		glVertex3d(a.b.x, a.b.y, a.b.z);
		glVertex3d(a.c.x, a.c.y, a.c.z);
		glColor3f(0.5, 0., 0.);
	glEnd();
}

void DrawEngine::draw(const Plane &a)
{
}

void DrawEngine::draw(const EmptyPS &a)
{
}

void DrawEngine::draw(const PointSet &a)
{
}

void DrawEngine::draw(const SquareAA &a)
{
	glBegin(GL_QUADS);
		const Vector &n = a.normal();
		glNormal3d(n.x, n.y, n.z);
		for(int i = 0; i < 4; ++i)
		{
			const Vector &v = a.getVertex(i);
			glVertex3d(v.x, v.y, v.z);
		}
	glEnd();
}

void DrawEngine::draw(const RectangleAA &a)
{
	glBegin(GL_QUADS);
		glColor3f(0.7f, 0.7f, 0.0f);
		const Vector &n = a.normal();
		glNormal3d(n.x, n.y, n.z);
		for(int i = 0; i < 4; ++i)
		{
			const Vector &v = a.getVertex(i);
			glVertex3d(v.x, v.y, v.z);
		}
		glColor3f(0.5f, 0.0f, 0.0f);
	glEnd();
}

void DrawEngine::draw(PointSet *a)
{
	if(Vector *p = dynamic_cast<Vector*>(a))
		draw(*p);
	else if(World *p = dynamic_cast<World*>(a))
		draw(*p);
	else if(Line *p = dynamic_cast<Line*>(a))
		draw(*p);
	else if(Ray *p = dynamic_cast<Ray*>(a))
		draw(*p);
	else if(Segment *p = dynamic_cast<Segment*>(a))
		draw(*p);
	else if(Triangle *p = dynamic_cast<Triangle*>(a))
		draw(*p);
	else if(Plane *p = dynamic_cast<Plane*>(a))
		draw(*p);
	else if(EmptyPS *p = dynamic_cast<EmptyPS*>(a))
		draw(*p);
	else if(Cube *p = dynamic_cast<Cube*>(a))
		draw(*p);
	else if(Box *p = dynamic_cast<Box*>(a))
		draw(*p);
	else if(SquareAA *p = dynamic_cast<SquareAA*>(a))
		draw(*p);
	else if(RectangleAA *p = dynamic_cast<RectangleAA*>(a))
		draw(*p);
}

void DrawEngine::draw(const World &a)
{
	glColor3d(1., 0.1, .5);
	for(int i = 0; i < a.dimx; ++i)
		for(int j = 0; j < a.dimy; ++j)
			draw(*a.worldChunk[i][j]);
}

void DrawEngine::draw(const WorldChunk &a)
{
	for(int i = 0; i < 6; ++i)
	{
		glNormal3dv((double*)&Cube::normals[i]);
		glVertexPointer(3, GL_DOUBLE, 0, a.quadArray[i]);
		glDrawArrays(GL_QUADS, 0, a.qacnt[i] / 3);
	}
}

void DrawEngine::addToBuffer(PointSet *a)
{
	PSBuffer.push_back(a);
}

void DrawEngine::drawBuffer()
{
	for(list<PointSet*>::iterator i = PSBuffer.begin(); i != PSBuffer.end(); ++i)
		draw(*i);
}

void DrawEngine::drawText(TextObject *t) 
{
	glRasterPos2d(t->x, t->y);
	glColor3d(t->clr.r, t->clr.g, t->clr.b);
	glutBitmapString(t->font, (const unsigned char*) t->text.c_str());
}

void DrawEngine::addToTextBuffer(TextObject *a)
{
	textBuffer.push_back(a);
}

void DrawEngine::drawTextBuffer(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, w, 0.0, h);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	for(list<TextObject*>::iterator i = textBuffer.begin(); i != textBuffer.end(); ++i)
		drawText(*i);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}
