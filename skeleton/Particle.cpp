#include "Particle.h"
#include <iostream>
#include <fstream>


Particle::Particle(Vector3D Pos, Vector3D Vel, Vector3D Accel)
{

	vel = Vel;
	accel = Accel;
	pos.p = { Pos.x,Pos.y,Pos.z};
	pos.q = { 0,0,0,0 };
	item = new RenderItem(CreateShape(PxSphereGeometry(1)), &pos, { 1,1,1,1 });
}

Particle::~Particle()
{
	DeregisterRenderItem(item);
	item = nullptr;
}

void Particle::integrate(double t)
{
	
	pos.q.x=vel.x*t;
	pos.q.y=vel.y*t;
	pos.q.z=vel.z*t;
	vel += accel * t;
	vel =vel* pow(damping, t);
	accel = accel* pow(damping, t);
}



