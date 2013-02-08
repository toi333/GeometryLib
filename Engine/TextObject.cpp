#include "StdAfx.h"
#include "TextObject.h"

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/freeglut.h>
#else
#include <GL/freeglut.h>
#endif


TextObject::TextObject(void)
{
}

TextObject::TextObject(const std::string &_text, double _x, double _y, const Color &_clr, void *_font)
	: text(_text), x(_x), y(_y), clr(_clr), font(_font)
{
}

TextObject::TextObject(const std::string &_text, double _x, double _y)
	: text(_text), x(_x), y(_y), clr(Color(0.7, 0.2, 0.2)), font(GLUT_BITMAP_HELVETICA_10)
{

}


TextObject::~TextObject(void)
{
}
