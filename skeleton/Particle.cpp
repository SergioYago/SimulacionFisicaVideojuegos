#include "Particle.h"
Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Accel)
{
	vel = Vel;
	accel = Accel;
	pos.p = Pos;
	pos.q = { 0,0,0,0 };
	item = new RenderItem(CreateShape(PxSphereGeometry(10)), &pos, { 1,1,1,1 });
}

Particle::~Particle()
{
	DeregisterRenderItem(item);
	item = nullptr;
}

void Particle::integrate(double t)
{
	pos.p += vel * t;
	vel += accel * t;
	vel *= pow(damping, t);
	accel *= pow(damping, t);
}

void Particle::update(double t)
{
	
}

