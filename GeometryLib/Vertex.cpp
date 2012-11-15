#include "StdAfx.h"
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

Vector Vertex::pos() const
{
	return *this;
}
