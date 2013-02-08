#pragma once
#include "Color.h"
#include <string>

class TextObject
{
public:
	TextObject(void);
	TextObject(const std::string &_text, double _x, double _y, const Color &_clr, void *_font);
	TextObject(const std::string &_text, double _x, double _y);
	~TextObject(void);

	Color clr;
	std::string text;
	double x, y;
	void *font;
};

