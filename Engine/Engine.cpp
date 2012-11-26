#include "stdafx.h"
#include "Engine.h"

using namespace std;

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

DrawEngine Engine::de;
Player Engine::c;
PhysicsProcessor Engine::PP;

void Engine::nextFrame()
{
	static double lt = 0;
	double t = glutGet(GLUT_ELAPSED_TIME) / 1000.;
	double dt = t - lt;
	lt = t;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glLoadIdentity();

	glColor3f(0.5, 0., 0.);

	PP.updateList(dt);

	c.transform();

	for(list<PhysicsObject*>::iterator it = PP.phList.begin(); it != PP.phList.end(); ++it)
		if(CubePH *qwe = dynamic_cast<CubePH*>(*it))
			qwe->blah = (*it)->flr != 0;

	de.drawBuffer();

	glutSwapBuffers();
}

void Engine::handleResize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
	glMatrixMode(GL_MODELVIEW);
}

void Engine::idle(void)
{
	glutPostRedisplay();
}

void Engine::initRendering(int argc, char **argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 500);
	glutCreateWindow("Test");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);

	glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

	glutIgnoreKeyRepeat(true);

	glutDisplayFunc(nextFrame);
	glutReshapeFunc(handleResize);
	glutKeyboardFunc(handleKeyDown);
	glutKeyboardUpFunc(handleKeyUp);
	glutPassiveMotionFunc(handleMouseMove);
	glutMouseFunc(mouseFunc);
	glutIdleFunc(idle);

	glutMainLoop();
}

void Engine::start(int argc, char **argv)
{
	Triangle T(Vector(-3, 0, 3), Vector(3, 0, 0), Vector(-3, 0, -3));
	Cube cb(Vector(0., 0., 0.), 1.);
	SquareAAPH sq(SquareAA(Vector(), 10., XP), Vector(), 1, 1);
	BoxPH *bx = new BoxPH(Box(Vector(3, 2, 1), Vector(1, 2, 3)));
	CubePH *bx2 = new CubePH(Cube(Vector(3, -6, 2), 1));

	BoxPH *flr = new BoxPH(Box(Vector(0, -20, 0), Vector(20, 1, 20)), Vector(), 1, 1);


	PP.phList.push_back(bx);
	PP.phList.push_back(bx2);
	PP.phList.push_back(flr);
	PP.phList.push_back(&c);

	de.addToBuffer(&T);
	de.addToBuffer(&cb);
	de.addToBuffer(&sq);
	de.addToBuffer(bx);
	de.addToBuffer(bx2);
	de.addToBuffer(flr);

	for(int i = 0; i < 10; ++i)
	{
		CubePH *q = new CubePH(Cube(Vector(10, 0, i), 0.3));
		de.addToBuffer(q);
		PP.phList.push_back(q);
	}

	initRendering(argc, argv);
}


void Engine::handleKeyDown(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 27: //Esc
		exit(0);
		break;
	case 'w':
		c.move(Vector(0, 0, -1));
		break;
	case 's':
		c.move(Vector(0, 0, 1));
		break;
	case 'a':
		c.move(Vector(-1, 0, 0));
		break;
	case 'd':
		c.move(Vector(1, 0, 0));
		break;
	case 'q':
		c.move(Vector(0, -1, 0));
		break;
	case 'e':
		c.move(Vector(0, 1, 0));
		break;
	case 'g':
		PhysicsObject::gravity = Vector(0, -10, 0) - PhysicsObject::gravity;
		break;
	case ' ':
		c.jump();
		break;
	case 'r':
		c.p = Vector();
		c.vel = Vector();
	}
}

void Engine::handleKeyUp(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'w':
		c.move(Vector(0, 0, 1));
		break;
	case 's':
		c.move(Vector(0, 0, -1));
		break;
	case 'a':
		c.move(Vector(1, 0, 0));
		break;
	case 'd':
		c.move(Vector(-1, 0, 0));
		break;
	case 'q':
		c.move(Vector(0, 1, 0));
		break;
	case 'e':
		c.move(Vector(0, -1, 0));
		break;
	}
}

void Engine::handleMouseMove(int x, int y)
{
	if(x == glutGet(GLUT_WINDOW_WIDTH) / 2 && y == glutGet(GLUT_WINDOW_HEIGHT) / 2)
		return;
	c.rotate(x - glutGet(GLUT_WINDOW_WIDTH) / 2, y - glutGet(GLUT_WINDOW_HEIGHT) / 2);
	SetCursorPos(glutGet(GLUT_WINDOW_X) + glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_Y) + glutGet(GLUT_WINDOW_HEIGHT) / 2);
}

void Engine::mouseFunc(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		fireRay(Ray(c.p, (c.getCameraDirection() + c.p)));
	else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		CubePH *cph = new CubePH(Cube(c.p, 0.3), c.getCameraDirection() * 3);
		//SquareAAPH *sph = new SquareAAPH(SquareAA(c.p, 0.3, XP), c.getCameraDirection() * 3);
		PP.phList.push_back(cph);
		de.addToBuffer(cph);
	}
}

void Engine::fireRay(const Ray &r, int maxBounces)
{
	if(maxBounces < 0)
		return;
	double mn = INF;
	Vector n;
	for(list<PointSet*>::const_iterator it = de.PSBuffer.begin(); it != de.PSBuffer.end(); ++it)
	{
		if(Surface *sf = dynamic_cast<Surface*>(*it))
		{
			double a = r.hit(sf);
			if(a < mn && a > EPS)
			{
				n = sf->normal();
				mn = a;
			}
		}
		else if(VolumetricObject *cb = dynamic_cast<VolumetricObject*>(*it))
		{
			pair<double, Vector> pdv = cb->reflect(r);
			if(pdv.first < mn && pdv.first > EPS)
			{
				mn = pdv.first;
				n = pdv.second;
			}
		}
	}
	if(mn != INF)
	{
		Vector x(r.a + r.b * mn);
		de.addToBuffer(new Segment(r.a, x));
		fireRay(Ray(x, r.b - 2 * dotProduct(n, r.b) * n + x), maxBounces - 1);
	}
	else
		de.addToBuffer(new Ray(r));
}
