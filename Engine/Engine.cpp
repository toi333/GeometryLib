#include "stdafx.h"
#include "Engine.h"
#include <ctime>

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
Player Engine::ply;
PhysicsProcessor Engine::PP;
World Engine::w;
const double Engine::updateInterval = 1. / 60.;
double Engine::updateTimeLeft = 0.;
int Engine::windowHeight = 500, Engine::windowWidth = 800;


void Engine::nextFrame()
{
	static double lt = 0;
	double t = glutGet(GLUT_ELAPSED_TIME) / 1000.;
	double dt = t - lt;
	lt = t;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)windowWidth / windowHeight, 0.55, 200.0);
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glLoadIdentity();

	glColor3f(0.5, 0., 0.);

	for(updateTimeLeft += dt; updateTimeLeft > updateInterval; updateTimeLeft -= updateInterval)
		PP.updateList(updateInterval);

	ply.cam.transform();

	for(list<PhysicsObject*>::iterator it = PP.phList.begin(); it != PP.phList.end(); ++it)
		if(CubePH *qwe = dynamic_cast<CubePH*>(*it))
			qwe->blah = (*it)->flr != 0;

	de.drawBuffer();

	char s[20];
	sprintf(s, "%lf", ply.vel.length());
	TextObject txt(s, 5, 5);
	de.addToTextBuffer(&txt);

	de.drawTextBuffer(windowWidth, windowHeight);
	de.textBuffer.clear();
	
	glutSwapBuffers();
}

void Engine::handleResize(int w, int h)
{
	windowWidth = w;
	windowHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / h, 0.55, 200.0);
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
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Test");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);

	glEnableClientState(GL_VERTEX_ARRAY);

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

	printf("%s\n", glGetString(GL_VERSION));
	glutMainLoop();
}

void Engine::start(int argc, char **argv)
{
	srand((int)time(0));
	//Triangle T(Vector(-3, 0, 3), Vector(3, 0, 0), Vector(-3, 0, -3));
	//Cube cb(Vector(0., 0., 0.), 1.);
	//BoxPH *bx = new BoxPH(Box(Vector(3, 2, 1), Vector(1, 2, 3)));
	//CubePH *bx2 = new CubePH(Cube(Vector(3, -6, 2), 1));

	BoxPH *flr = new BoxPH(Box(Vector(0, -30, 0), Vector(20, 1, 20)), Vector(), 1, 1);

	////PP.phList.push_back(bx);
	//PP.phList.push_back(bx2);
	PP.phList.push_back(flr);
	PP.phList.push_back(&ply);

	//de.addToBuffer(&T);
	//de.addToBuffer(&cb);
	////de.addToBuffer(bx);
	//de.addToBuffer(bx2);
	de.addToBuffer(flr);

	//for(int i = 0; i < 10; ++i)
	//{
	//	CubePH *q = new CubePH(Cube(Vector(10, 0, i), 0.3));
	//	de.addToBuffer(q);
	//	PP.phList.push_back(q);
	//}
	initWorld();
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
		ply.move(Vector(0, 0, -1));
		break;
	case 's':
		ply.move(Vector(0, 0, 1));
		break;
	case 'a':
		ply.move(Vector(-1, 0, 0));
		break;
	case 'd':
		ply.move(Vector(1, 0, 0));
		break;
	case 'q':
		ply.move(Vector(0, -1, 0));
		break;
	case 'e':
		ply.move(Vector(0, 1, 0));
		break;
	case 'g':
		PhysicsObject::gravity = Vector(0, -25, 0) - PhysicsObject::gravity;
		break;
	case ' ':
		ply.jump();
		break;
	case 'r':
		ply.p = Vector();
		ply.vel = Vector();
	}
}

void Engine::handleKeyUp(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'w':
		ply.move(Vector(0, 0, 1));
		break;
	case 's':
		ply.move(Vector(0, 0, -1));
		break;
	case 'a':
		ply.move(Vector(1, 0, 0));
		break;
	case 'd':
		ply.move(Vector(-1, 0, 0));
		break;
	case 'q':
		ply.move(Vector(0, 1, 0));
		break;
	case 'e':
		ply.move(Vector(0, -1, 0));
		break;
	}
}

void Engine::handleMouseMove(int x, int y)
{
	if(x == glutGet(GLUT_WINDOW_WIDTH) / 2 && y == glutGet(GLUT_WINDOW_HEIGHT) / 2)
		return;
	ply.cam.rotate(x - glutGet(GLUT_WINDOW_WIDTH) / 2, y - glutGet(GLUT_WINDOW_HEIGHT) / 2);
	SetCursorPos(glutGet(GLUT_WINDOW_X) + glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_Y) + glutGet(GLUT_WINDOW_HEIGHT) / 2);
}

void Engine::mouseFunc(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		bounceRay(Ray(ply.cam.p, ply.cam.getCameraDirection() + ply.cam.p));
		if(PointSet *p = fireRay(Ray(ply.cam.p, ply.cam.getCameraDirection() + ply.cam.p)))
			if(PhysicsObject *po = dynamic_cast<PhysicsObject*>(p))
				po->vel += 2. * ply.cam.getCameraDirection() / po->mass;
		//splitBox(Ray(ply.cam.p, ply.cam.getCameraDirection() + ply.cam.p));
	}
	else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		CubePH *cph = new CubePH(Cube(ply.cam.p + ply.cam.getCameraDirection() * 1.8, 0.3), ply.cam.getCameraDirection() * 3 + ply.vel);
		PP.phList.push_back(cph);
		de.addToBuffer(cph);
	}
}

PointSet* Engine::fireRay(const Ray &r)
{
	double mn = INF;
	PointSet* ret = 0;
	for(list<PointSet*>::const_iterator it = de.PSBuffer.begin(); it != de.PSBuffer.end(); ++it)
	{
		if(Surface *sf = dynamic_cast<Surface*>(*it))
		{
			double a = r.hit(sf);
			if(a < mn && a > EPS)
			{
				mn = a;
				ret = *it;
			}
		}
		else if(VolumetricObject *cb = dynamic_cast<VolumetricObject*>(*it))
		{
			pair<double, Vector> pdv = cb->reflect(r);
			if(pdv.first < mn && pdv.first > EPS)
			{
				mn = pdv.first;
				ret = *it;
			}
		}
	}
	return ret;
}

void Engine::bounceRay(const Ray &r, int maxBounces)
{
	if(maxBounces < 0)
		return;
	if(PointSet *p = fireRay(r))
	{
		double d;
		Vector n;
		if(Surface *sf = dynamic_cast<Surface*>(p))
		{
			d = r.hit(sf);
			n = sf->normal();
		}
		else if(VolumetricObject *vo = dynamic_cast<VolumetricObject*>(p))
		{
			pair<double,Vector> pdv = vo->reflect(r);
			d = pdv.first;
			n = pdv.second;
		}
		Vector x(r.a + r.b * d);
		de.addToBuffer(new Segment(r.a, x));
		bounceRay(Ray(x, r.b - 2 * dotProduct(n, r.b) * n + x), maxBounces - 1);
	}
	else
		de.addToBuffer(new Ray(r));
}

void Engine::splitBox(const Ray &r)
{
	if(PointSet *p = fireRay(r))
	{
		if(BoxPH *bx = dynamic_cast<BoxPH*>(p))
		{
			if(bx->frozen)
				return;
			pair<double, Vector> pdv = bx->reflect(r);
			Vector v = pdv.first * r.b + r.a;
			Vector &n = pdv.second;
			if(
				n.x && bx->d.y - abs(bx->a.y - v.y) < bx->d.z - abs(bx->a.z - v.z) ||
			    n.z && bx->d.y - abs(bx->a.y - v.y) < bx->d.x - abs(bx->a.x - v.x))
			{
				BoxPH *nbx = new BoxPH(Box(
					Vector(bx->a.x, (v.y + bx->a.y - bx->d.y) / 2., bx->a.z),
					Vector(bx->d.x, (bx->d.y + v.y - bx->a.y) / 2., bx->d.z)),
					bx->vel);
				de.addToBuffer(nbx);
				PP.phList.push_back(nbx);
				*bx = BoxPH(Box(
					Vector(bx->a.x, (v.y + bx->a.y + bx->d.y) / 2., bx->a.z),
					Vector(bx->d.x, (bx->d.y + bx->a.y - v.y) / 2., bx->d.z)),
					bx->vel);
				nbx->vel.y -= bx->mass / (bx->mass + nbx->mass);
				bx->vel.y += nbx->mass / (bx->mass + nbx->mass);
			}
			else if(
				n.y && bx->d.x - abs(bx->a.x - v.x) < bx->d.z - abs(bx->a.z - v.z) ||
				n.z && bx->d.x - abs(bx->a.x - v.x) < bx->d.y - abs(bx->a.y - v.y))
			{
				BoxPH *nbx = new BoxPH(Box(
					Vector((v.x + bx->a.x - bx->d.x) / 2., bx->a.y, bx->a.z),
					Vector((bx->d.x + v.x - bx->a.x) / 2., bx->d.y, bx->d.z)),
					bx->vel);
				de.addToBuffer(nbx);
				PP.phList.push_back(nbx);
				*bx = BoxPH(Box(
					Vector((v.x + bx->a.x + bx->d.x) / 2., bx->a.y, bx->a.z),
					Vector((bx->d.x + bx->a.x - v.x) / 2., bx->d.y, bx->d.z)),
					bx->vel);
				nbx->vel.x -= bx->mass / (bx->mass + nbx->mass);
				bx->vel.x += nbx->mass / (bx->mass + nbx->mass);
			}
			else
			{
				BoxPH *nbx = new BoxPH(Box(
					Vector(bx->a.x, bx->a.y, (v.z + bx->a.z - bx->d.z) / 2.),
					Vector(bx->d.x, bx->d.y, (bx->d.z + v.z - bx->a.z) / 2.)),
					bx->vel);
				de.addToBuffer(nbx);
				PP.phList.push_back(nbx);
				*bx = BoxPH(Box(
					Vector(bx->a.x, bx->a.y, (v.z + bx->a.z + bx->d.z) / 2.),
					Vector(bx->d.x, bx->d.y, (bx->d.z + bx->a.z - v.z) / 2.)),
					bx->vel);
				nbx->vel.z -= bx->mass / (bx->mass + nbx->mass);
				bx->vel.z += nbx->mass / (bx->mass + nbx->mass);
			}
		}
	}
}


void Engine::initWorld()
{
	w.generateWorld();
	PP.phList.push_back(&w);
	de.addToBuffer(&w);
}