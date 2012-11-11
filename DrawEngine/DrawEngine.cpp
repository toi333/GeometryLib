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
	for(int i = 0; i < 6; ++i)
		draw(a.getSide(i));
}

void DrawEngine::draw(const Vector &a)
{
	glPushMatrix();
		glTranslated(a.x, a.y, a.z);
		glutSolidSphere(.1, 10., 10.);
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
		glColor3f(0.0f, 0.0f, 0.7f);
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
	switch(a->type())
	{
	case VECTOR:
		draw(*(Vector*)a);
		break;
	case LINE:
		draw(*(Line*)a);
		break;
	case RAY:
		draw(*(Ray*)a);
		break;
	case SEGMENT:
		draw(*(Segment*)a);
		break;
	case TRIANGLE:
		draw(*(Triangle*)a);
		break;
	case PLANE:
		draw(*(Plane*)a);
		break;
	case EMPTYPS:
		draw(*(EmptyPS*)a);
		break;
	case CUBE:
		draw(*(Cube*)a);
		break;
	case SQUAREAA:
		draw(*(SquareAA*)a);
		break;
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
