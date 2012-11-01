#include "StdAfx.h"
#include "Camera.h"

#define _USE_MATH_DEFINES
#include <math.h>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


void Camera::transform(void) const
{
	glRotated(pitch, 1., 0., 0.);
	glRotated(yaw, 0., 1., 0.);
	glTranslated(-p.x, -p.y, -p.z);
}

void Camera::update(double t)
{
	double phix = yaw * M_PI / 180.;
	double phiy = pitch * M_PI / 180.;
	Vector v
	(
		dir.x,
		dir.z * sin(phiy),
		dir.z * cos(phiy)
	);
	v = Vector
	(
		v.x * cos(phix) - v.z * sin(phix),
		v.y,
		v.x * sin(phix) + v.z * cos(phix)
	);
	p += (v + Vector(0, dir.y, 0)).normalized() * t * 7.;
}

void Camera::rotate(int x, int y)
{
	yaw   += (double)x * 0.8;
	pitch += (double)y * 0.8;
	if(pitch > 90)
		pitch = 90;
	else if(pitch < -90)
		pitch = -90;
}

void Camera::move(const Vector &_dir)
{
	dir += _dir;
}

Vector Camera::getCameraDirection(void) const
{
	double phix = yaw * M_PI / 180.;
	double phiy = pitch * M_PI / 180.;
	return Vector
	(
		 cos(phiy) * sin(phix),
		-sin(phiy),
		-cos(phiy) * cos(phix)
	);
}
