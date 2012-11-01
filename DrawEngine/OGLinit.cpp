#include "StdAfx.h"
#include "GeometryLib.h"
#include "OGLinit.h"

using namespace std;

int windowHeight = 500;
int windowWidth = 800;
double camSpeed = 1.;
Camera *cam;

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

void setCam(Camera &c)
{
	cam = &c;
}

void handleKeyDown(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 27: //Esc
		exit(0);
		break;
	case 'w':
		cam->move(Vector(0, 0, -1));
		break;
	case 's':
		cam->move(Vector(0, 0, 1));
		break;
	case 'a':
		cam->move(Vector(-1, 0, 0));
		break;
	case 'd':
		cam->move(Vector(1, 0, 0));
		break;
	case 'q':
		cam->move(Vector(0, -1, 0));
		break;
	case 'e':
		cam->move(Vector(0, 1, 0));
		break;
	}
}

void handleKeyUp(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'w':
		cam->move(Vector(0, 0, 1));
		break;
	case 's':
		cam->move(Vector(0, 0, -1));
		break;
	case 'a':
		cam->move(Vector(1, 0, 0));
		break;
	case 'd':
		cam->move(Vector(-1, 0, 0));
		break;
	case 'q':
		cam->move(Vector(0, 1, 0));
		break;
	case 'e':
		cam->move(Vector(0, -1, 0));
		break;
	}
}

void handleResize(int w, int h)
{
	windowWidth = w;
	windowHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
	glMatrixMode(GL_MODELVIEW);
}

void handleMouseMove(int x, int y)
{
	if(x == windowWidth / 2 && y == windowHeight / 2)
		return;
	cam->rotate(x - windowWidth / 2, y - windowHeight / 2);
	SetCursorPos(glutGet(GLUT_WINDOW_X) + windowWidth / 2, glutGet(GLUT_WINDOW_Y) + windowHeight / 2);
}

void mouseFunc(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		Ray *r = new Ray(cam->p, (cam->getCameraDirection() + cam->p));
		addToBuffer(r);

		for(list<PointSet*>::const_iterator it = getBuffer().begin(); it != getBuffer().end(); ++it)
		{
			if((*it)->type() == TRIANGLE)
			{
				Intersection I;
				I.intersect(*r, *(Triangle*)*it);
				if(I.get()->type() == VECTOR)
					addToBuffer(new Vector(*(Vector*)I.get()));
			}
		}
	}
}

void idle(void)
{
	glutPostRedisplay();
}

void initRendering(int argc, char **argv, void (*drawFunc)(void)) 
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

	glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

	glutIgnoreKeyRepeat(true);

	glutDisplayFunc(drawFunc);
	glutReshapeFunc(handleResize);
	glutKeyboardFunc(handleKeyDown);
	glutKeyboardUpFunc(handleKeyUp);
	glutPassiveMotionFunc(handleMouseMove);
	glutMouseFunc(mouseFunc);
	glutIdleFunc(idle);

	glutMainLoop();
}