#include "stdafx.h"
#include "GeometryLib.h"
#include "OGLinit.h"

Camera c;

void drawScene() 
{
	static double lt = 0;
	double t = glutGet(GLUT_ELAPSED_TIME) / 1000.;
	double dt = t - lt;
	lt = t;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glLoadIdentity();

	c.update(dt);
	c.transform();

	glColor3f(0.5, 0., 0.);

	drawBuffer();
	//glutSolidCube(5);

	glutSwapBuffers();
}


int _tmain(int argc,  char **argv)
{
	/*Vector v(0, 0, 0);
	Line l(Vector(0., 0., 0.), Vector(-2., 1., 0.));
	Triangle T(Vector(0., 0., 0.), Vector(-5., 5., 0.), Vector(5., 5., 0.));
	Ray R(Vector(0., 0., 0.), Vector(2., 21., 0.));
	Segment S(Vector(-5., 0., 0.), Vector(0., -5., 0.));

	PointSet *p = new Triangle(Vector(0., 0., 1.), Vector(-5., 5., 1.), Vector(5., 5., 3.));

	addToBuffer(&v);
	addToBuffer(&l);
	addToBuffer(&T);
	addToBuffer(&R);
	addToBuffer(&S);
	addToBuffer(p);*/

	Ray r(Vector(1., 1., -5.), Vector(1., -1., 0.));
	Triangle T(Vector(-3, 0, 3), Vector(3, 0, 0), Vector(-3, 0, -3));
	Plane pi(Vector(0., -5., 0.), Vector(0., 1., 0.));
	Cube cb(Vector(0., 0., 0.), 1.);
	SquareAA sq(Vector(), 10., XP);
	
	Intersection I;
	I.intersect(r, pi);
	addToBuffer(I.get());
	addToBuffer(&pi);
	addToBuffer(&r);
	addToBuffer(&T);
	addToBuffer(&cb);
	addToBuffer(&sq);
	setCam(c);

	initRendering(argc, argv, drawScene);
	return 0;
}