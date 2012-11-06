#pragma once

#include <windows.h>
#include "DrawEngine.h"
#include "GeometryLib.h"
#include "CubePH.h"
#include "Camera.h"

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void handleResize(int w, int h);

void idle(void);

void initRendering(int argc, char **argv, void (*drawFunc)(void));
