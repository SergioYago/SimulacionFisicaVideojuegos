#include "Particle.h"
#include <iostream>
#include <fstream>




Particle::Particle(Vector3D Pos, Vector3D Vel, Vector3D Accel, float Grav, float Lifetime)
{
	vel = Vel;
	accel = Accel;
	pos.p = { (float)Pos.x,(float)Pos.y,(float)Pos.z };
	pos.q = { 0,0,0,0 };
	item = new RenderItem(CreateShape(PxSphereGeometry(1)), &pos, { 1,1,1,1 });
	grav = Grav;
	lifetime = Lifetime;
}

Particle::~Particle()
{
	DeregisterRenderItem(item);
	item = nullptr;
}

void Particle::integrate(double t)
{
	pos.p.x+=vel.x*t;
	pos.p.y+=vel.y*t;
	pos.p.z+=vel.z*t;
	vel += accel * t;
	vel.y -= grav * t;
	vel =vel* pow(damping, t);
	accel = accel* pow(damping, t);
}

bool Particle::canDestroy(double t)
{
	lifetime -= t;
	return lifetime<=0;
}



