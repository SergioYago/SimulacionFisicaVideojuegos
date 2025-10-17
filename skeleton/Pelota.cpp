#include "Pelota.h"
Pelota::Pelota(Vector3D posfinal, PelotaSystem* System, Vector3D pos, Vector3D dir, Vector3D accel, float grav, float lifetime) :Particle(pos, dir, accel, grav, lifetime)
{
	posFinal = posfinal;
	system = System;
}

Pelota::~Pelota()
{
	Particle::~Particle();
}

void Pelota::integrate(double t)
{
	Particle::integrate(t);
	Vector3D aux = getPos();
	//como compruebo esto?
	if(aux.x<posFinal.x||aux.y>posFinal.y||aux.z>posFinal.z)
	{
		system->Activate();
	}
}
