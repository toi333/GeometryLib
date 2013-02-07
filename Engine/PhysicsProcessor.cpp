#include "StdAfx.h"
#include "PhysicsProcessor.h"

using namespace std;

PhysicsProcessor::PhysicsProcessor(void)
{
}

PhysicsProcessor::~PhysicsProcessor(void)
{
}

void PhysicsProcessor::collide(PhysicsObject *a, PhysicsObject *b)
{
	
	if(World *p = dynamic_cast<World*>(a))
	{
		collide(b, *p);
		return;
	}
	if(World *p = dynamic_cast<World*>(b))
	{
		collide(a, *p);
		return;
	}

	if(a->frozen && b->frozen)
		return;

	int n;
	double d = AABBIntersect(a->getAABB(), b->getAABB(), n);
	//if(d > -EPS)
	if(d > EPS)
	{
		if(a->flr == b && d > EPS)
			a->flr = 0;
		if(b->flr == a && d > EPS)
			b->flr = 0;
		return;
	}
	applyCollisionAA(*a, *b, n, -d);
}

void PhysicsProcessor::collide(PhysicsObject *a, World &b)
{
	Box bx = a->getAABB();
	bx.a += Vector((double)b.dimx, 0., (double)b.dimz);

	Vector v1 = (bx.a - bx.d) / 2. - Vector(1);
	Vector v2 = (bx.a + bx.d) / 2. + Vector(2);
	v1.x = max(v1.x, 0.);
	v1.y = max(v1.y, 0.);
	v1.z = max(v1.z, 0.);
	v2.x = min(v2.x, (double)b.dimx);
	v2.y = min(v2.y, (double)b.dimy);
	v2.z = min(v2.z, (double)b.dimz);

	if(a->flr == &b)
		a->flr = 0;
	for(int i = (int)v1.x; i < (int)v2.x; ++i)
		for(int j = (int)v1.y; j < (int)v2.y; ++j)
			for(int k = (int)v1.z; k < (int)v2.z; ++k)
				if(b.worldBlock[i][j][k])
				{
					CubePH t(b.getBlockAtIdx(i, j, k), Vector(), 1., 1);
					collide(a, &t);
					if(a->flr == &t)
						a->flr = &b;
				}
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
	bool neg = 0;
	double *av = 0, *bv = 0;

	if(sgn(a.vel[n] - b.vel[n]) == sgn(a.getPos()[n] - b.getPos()[n]))
		return;
	av = &a.vel[n];
	bv = &b.vel[n];
	neg = b.getPos()[n] < a.getPos()[n];

	double avt = *av;
	double bvt = *bv;

	Vector no(n == 0, n == 1, n == 2);
	if(neg)
		no = -no;
	if(!a.frozen && !b.frozen && (n != 1 || n == 1 && neg && !b.flr || n == 1 && !neg && !a.flr))
	{
		double ca = 1., cb = 1.;
		if(abs(avt) > EPS && abs(bvt) > EPS)
		{
			ca = abs(avt);
			cb = abs(bvt);
		}
		ca /= a.mass;
		cb /= b.mass;
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
		if(n == 1 && *bv < 1)
		{
			b.flr = &a;
			b.vel.y = 0;
		}
	}
	else if(b.frozen || b.flr && n == 1 && neg)
	{
		a.setPos(a.getPos() - no * d);
		a.vel *= 1 - PhysicsObject::collisionFriction;
		*av = -PhysicsObject::collisionElasticity * avt;
		if(n == 1 && *av < 1)
		{
			a.flr = &b;
			a.vel.y = 0;
		}
	}
}

double PhysicsProcessor::AABBIntersect(const Box &a, const Box &b, int &n)
{
	double md = -INF;
	for(int i = 0; i < 3; ++i)
	{
		double d = intervalDistance(a.a[i] - a.d[i], a.a[i] + a.d[i], b.a[i] - b.d[i], b.a[i] + b.d[i]);
		//if(d > -EPS)
		if(d > EPS)
			return d;
		if(d > md)
		{
			n = i;
			md = d;
		}
	}
	return md;
}
