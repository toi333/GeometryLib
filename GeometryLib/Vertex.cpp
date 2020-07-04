#include "Vertex.h"


Vertex::Vertex(void)
{
}

Vertex::Vertex(const Vector &v)
	: Vector(v)
{
}

Vertex::~Vertex(void)
{
}

Vector Vertex::getPos() const
{
	return *this;
}

void Vertex::setPos(const Vector &_v)
{
	*this = _v;
}
