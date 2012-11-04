#pragma once

#include <windows.h>
#include "DrawEngine.h"
#include "GeometryLib.h"
#include "CubePH.h"

void setCam(Camera &c);

void handleKeyDown(unsigned char key, int x, int y);

void handleKeyUp(unsigned char key, int x, int y);

void handleResize(int w, int h);

void handleMouseMove(int x, int y);

void idle(void);

void initRendering(int argc, char **argv, void (*drawFunc)(void));
