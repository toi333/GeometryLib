#include "StdAfx.h"
#include "PhysicsProcessor.h"

using namespace std;

PhysicsProcessor::PhysicsProcessor(void)
{
}

PhysicsProcessor::~PhysicsProcessor(void)
{
}

void PhysicsProcessor::collide(CubePH &a, CubePH &b)
{
	if(a.frozen && b.frozen)
		return;

	int n;
	double d, md = INF;
	d = intervalIntersection(a.a.x - a.d, a.a.x + a.d, b.a.x - b.d, b.a.x + b.d);
	if(d <= EPS)
		return;
	if(d < md)
	{
		n = 0;
		md = d;
	}
	d = intervalIntersection(a.a.y - a.d, a.a.y + a.d, b.a.y - b.d, b.a.y + b.d);
	if(d <= EPS)
		return;
	if(d < md)
	{
		n = 1;
		md = d;
	}
	d = intervalIntersection(a.a.z - a.d, a.a.z + a.d, b.a.z - b.d, b.a.z + b.d);
	if(d <= EPS)
		return;
	if(d < md)
	{
		n = 2;
		md = d;
	}

	applyCollisionAA(a, b, n, md);
}

void PhysicsProcessor::collide(BoxPH &a, BoxPH &b)
{
	if(a.frozen && b.frozen)
		return;

	int n;
	double d, md = INF;
	d = intervalIntersection(a.a.x - a.d.x, a.a.x + a.d.x, b.a.x - b.d.x, b.a.x + b.d.x);
	if(d <= EPS)
		return;
	if(d < md)
	{
		n = 0;
		md = d;
	}
	d = intervalIntersection(a.a.y - a.d.y, a.a.y + a.d.y, b.a.y - b.d.y, b.a.y + b.d.y);
	if(d <= EPS)
		return;
	if(d < md)
	{
		n = 1;
		md = d;
	}
	d = intervalIntersection(a.a.z - a.d.z, a.a.z + a.d.z, b.a.z - b.d.z, b.a.z + b.d.z);
	if(d <= EPS)
		return;
	if(d < md)
	{
		n = 2;
		md = d;
	}

	applyCollisionAA(a, b, n, md);
}

void PhysicsProcessor::collide(BoxPH &a, CubePH &b)
{
	if(a.frozen && b.frozen)
		return;

	int n;
	double d, md = INF;
	d = intervalIntersection(a.a.x - a.d.x, a.a.x + a.d.x, b.a.x - b.d, b.a.x + b.d);
	if(d <= EPS)
		return;
	if(d < md)
	{
		n = 0;
		md = d;
	}
	d = intervalIntersection(a.a.y - a.d.y, a.a.y + a.d.y, b.a.y - b.d, b.a.y + b.d);
	if(d <= EPS)
		return;
	if(d < md)
	{
		n = 1;
		md = d;
	}
	d = intervalIntersection(a.a.z - a.d.z, a.a.z + a.d.z, b.a.z - b.d, b.a.z + b.d);
	if(d <= EPS)
		return;
	if(d < md)
	{
		n = 2;
		md = d;
	}

	applyCollisionAA(a, b, n, md);
}

void PhysicsProcessor::collide(CubePH &a, BoxPH &b)
{
	collide(b, a);
}

void PhysicsProcessor::collide(PhysicsObject *a, PhysicsObject *b)
{
	if(CubePH *pa = dynamic_cast<CubePH*>(a))
	{
		if(CubePH *pb = dynamic_cast<CubePH*>(b))
			collide(*pa, *pb);
		else if(BoxPH *pb = dynamic_cast<BoxPH*>(b))
			collide(*pa, *pb);
		else if(Player *pb = dynamic_cast<Player*>(b))
			collide(*pa, *pb);
	}
	else if(BoxPH *pa = dynamic_cast<BoxPH*>(a))
	{
		if(CubePH *pb = dynamic_cast<CubePH*>(b))
			collide(*pa, *pb);
		else if(BoxPH *pb = dynamic_cast<BoxPH*>(b))
			collide(*pa, *pb);
		else if(Player *pb = dynamic_cast<Player*>(b))
			collide(*pa, *pb);
	}
	else if(Player *pa = dynamic_cast<Player*>(a))
	{
		if(CubePH *pb = dynamic_cast<CubePH*>(b))
			collide(*pa, *pb);
		else if(BoxPH *pb = dynamic_cast<BoxPH*>(b))
			collide(*pa, *pb);
	}
}

void PhysicsProcessor::collide(CubePH &a, SquareAAPH &b)
{
}

void PhysicsProcessor::collide(SquareAAPH &a, CubePH &b)
{
	collide(b, a);
}

void PhysicsProcessor::collide(SquareAAPH &b, SquareAAPH &a)
{
}

void PhysicsProcessor::collide(BoxPH &a, Player &b)
{
	if(a.frozen && b.frozen)
		return;

	int n;
	double d, md = INF;
	d = intervalIntersection(a.a.x - a.d.x, a.a.x + a.d.x, b.p.x - b.d, b.p.x + b.d);
	if(d <= EPS)
	{
		if(b.flr == &a)
			b.flr = 0;
		return;
	}
	if(d < md)
	{
		n = 0;
		md = d;
	}
	d = intervalIntersection(a.a.y - a.d.y, a.a.y + a.d.y, b.p.y - b.d, b.p.y + b.d);
	if(d <= EPS)
	{
		if(b.flr == &a)
			b.flr = 0;
		return;
	}
	if(d < md)
	{
		n = 1;
		md = d;
	}
	d = intervalIntersection(a.a.z - a.d.z, a.a.z + a.d.z, b.p.z - b.d, b.p.z + b.d);
	if(d <= EPS)
	{
		if(b.flr == &a)
			b.flr = 0;
		return;
	}
	if(d < md)
	{
		n = 2;
		md = d;
	}

	applyCollisionAA(a, b, n, md);
}

void PhysicsProcessor::collide(Player &a, BoxPH &b)
{
	collide(b, a);
}

void PhysicsProcessor::collide(CubePH &a, Player &b)
{
	if(a.frozen && b.frozen)
		return;

	int n;
	double d, md = INF;
	d = intervalIntersection(a.a.x - a.d, a.a.x + a.d, b.p.x - b.d, b.p.x + b.d);
	if(d <= EPS)
	{
		if(b.flr == &a)
			b.flr = 0;
		return;
	}
	if(d < md)
	{
		n = 0;
		md = d;
	}
	d = intervalIntersection(a.a.y - a.d, a.a.y + a.d, b.p.y - b.d, b.p.y + b.d);
	if(d <= EPS)
	{
		if(b.flr == &a)
			b.flr = 0;
		return;
	}
	if(d < md)
	{
		n = 1;
		md = d;
	}
	d = intervalIntersection(a.a.z - a.d, a.a.z + a.d, b.p.z - b.d, b.p.z + b.d);
	if(d <= EPS)
	{
		if(b.flr == &a)
			b.flr = 0;
		return;
	}
	if(d < md)
	{
		n = 2;
		md = d;
	}

	applyCollisionAA(a, b, n, md);
}

void PhysicsProcessor::collide(Player &a, CubePH &b)
{
	collide(b, a);
}


void PhysicsProcessor::updateList(double dt)
{
	for(list<PhysicsObject*>::iterator it = phList.begin(); it != phList.end(); ++it)
		(*it)->update(dt);

	for(list<PhysicsObject*>::iterator it = phList.begin(); it != phList.end(); ++it)
	{
		list<PhysicsObject*>::iterator jt = it;
		++jt;
		for(; jt != phList.end(); ++jt)
			collide(*it, *jt);
	}
}

//normala mora ici od a prema b
void PhysicsProcessor::applyCollision(PhysicsObject &a, PhysicsObject &b, const Vector &n)
{
	double dpa = dotProduct(a.vel, n);
	double dpb = dotProduct(b.vel, n);
	if(dpa - dpb > 0)
		return;
	Vector van = n * dpa;
	Vector vbn = n * dpb;
	Vector vat = a.vel - van;
	Vector vbt = b.vel - vbn;

	if(!a.frozen && !b.frozen)
	{
		a.vel = (PhysicsObject::collisionElasticity * b.mass * (vbn - van) + a.mass * van + b.mass * vbn) / (a.mass + b.mass)
			+ PhysicsObject::collisionFriction * vat;
		b.vel = (PhysicsObject::collisionElasticity * a.mass * (van - vbn) + b.mass * vbn + a.mass * van) / (b.mass + a.mass)
			+ PhysicsObject::collisionFriction * vbt;
	}
	else if(a.frozen)
		b.vel = PhysicsObject::collisionFriction * vbt - PhysicsObject::collisionElasticity * vbn;
	else
		a.vel = PhysicsObject::collisionFriction * vat - PhysicsObject::collisionElasticity * van;
}

void PhysicsProcessor::applyCollisionAA(PhysicsObject &a, PhysicsObject &b, int n, double d)
{
	//if(typeid(b) == typeid(Player))
	//	return;
	bool neg = 0;
	double *av = 0, *bv = 0;
	if(!n)
	{
		if(sgn(a.vel.x - b.vel.x) == sgn(a.getPos().x - b.getPos().x))
			return;
		av = &a.vel.x;
		bv = &b.vel.x;
		neg = b.getPos().x < a.getPos().x;

	}
	else if(n == 1)
	{
		if(sgn(a.vel.y - b.vel.y) == sgn(a.getPos().y - b.getPos().y))
			return;
		av = &a.vel.y;
		bv = &b.vel.y;
		neg = b.getPos().y < a.getPos().y;
	}
	else
	{
		if(sgn(a.vel.z - b.vel.z) == sgn(a.getPos().z - b.getPos().z))
			return;
		av = &a.vel.z;
		bv = &b.vel.z;
		neg = b.getPos().z < a.getPos().z;
	}
	double avt = *av;
	double bvt = *bv;

	Vector no(n == 0, n == 1, n == 2);
	if(neg)
		no = -no;
	if(!a.frozen && !b.frozen && (n != 1 || n == 1 && neg && !b.flr || n == 1 && !neg && !a.flr))
	{
		double ca = avt / a.mass;
		double cb = bvt / b.mass;
		a.setPos(a.getPos() - no * d * ca / (ca + cb));
		b.setPos(b.getPos() + no * d * cb / (cb + ca));
		a.vel *= 1 - PhysicsObject::collisionFriction;
		b.vel *= 1 - PhysicsObject::collisionFriction;
		*av = (PhysicsObject::collisionElasticity * b.mass * (bvt - avt) + a.mass * avt + b.mass * bvt) / (a.mass + b.mass);
		*bv = (PhysicsObject::collisionElasticity * a.mass * (avt - bvt) + b.mass * bvt + a.mass * avt) / (b.mass + a.mass);
		if(n == 1)
			a.flr = b.flr = 0;
	}
	else if(a.frozen || a.flr && n == 1 && !neg)
	{
		b.setPos(b.getPos() + no * d);
		b.vel *= 1 - PhysicsObject::collisionFriction;
		*bv = -PhysicsObject::collisionElasticity * bvt;
		if(n == 1 && *bv < 0.01)
			b.flr = &a;
	}
	else if(b.frozen || b.flr && n == 1 && neg)
	{
		a.setPos(a.getPos() - no * d);
		a.vel *= 1 - PhysicsObject::collisionFriction;
		*av = -PhysicsObject::collisionElasticity * avt;
		if(n == 1 && *av < 0.01)
			a.flr = &b;
	}
	else
		printf("omfg!!!!!!!!!!!\n");
}
