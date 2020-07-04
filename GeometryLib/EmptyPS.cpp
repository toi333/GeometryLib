#include "EmptyPS.h"

EmptyPS::EmptyPS(void)
{
}

EmptyPS::~EmptyPS(void)
{
}

Vector EmptyPS::getPos() const
{
	return Vector();
}

void EmptyPS::setPos(const Vector &_v)
{
	return;
}
