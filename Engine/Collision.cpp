#include "StdAfx.h"
#include "Collision.h"


Collision::Collision(void)
{
}

Collision::Collision(double _t, const Vector &_n)
	: t(_t), n(_n)
{
}


Collision::~Collision(void)
{
}

void Collision::collide(const CubePH &a, const CubePH &b)
{

}
