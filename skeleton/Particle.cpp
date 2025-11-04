#include "Particle.h"
#include <iostream>
#include <fstream>





Particle::Particle(Vector3D PosD, Vector3D Vel,float Mass, float Lifetime,float size)
{
	pos.p = { (float)PosD.x,(float)PosD.y,(float)PosD.z };
	pos.q = { 0,0,0,0 };
	vel = Vel;
	item = new RenderItem(CreateShape(PxSphereGeometry(size)), &pos, { 1,1,1,1 });
	mass = 1/Mass;
	lifetime = Lifetime;
	
}

Particle::~Particle()
{
	item->release();
	//DeregisterRenderItem(item);
	item = nullptr;
}

void Particle::integrate(double t)
{
	pos.p.x+=vel.x*t;
	pos.p.y+=vel.y*t;
	pos.p.z+=vel.z*t;
	vel += accel * t;
	vel =vel* pow(damping, t);
	accel = { 0,0,0 };
	
}

bool Particle::canDestroy(double t)
{
	lifetime -= t;
	return lifetime<=0;
}

void Particle::AddForce(Vector3D fuerza)
{
	accel += fuerza*mass;
}



