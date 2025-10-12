#include "Proyectile.h"
Proyectile::Proyectile(Vector3D pos,Vector3D vel, Vector3D Accel, float Mass,float g,float live):Particle(pos, vel, Accel)
{
	mass = Mass;
	grav = g;
	lifetime = live;
}

void Proyectile::integrate(double t)
{
	
	Particle::integrate(t);
	Vector3D aux = getVel();
	aux.y -= grav * mass * t;
	setVel(aux);
}

bool Proyectile::canDestroy(double t)
{
	lifetime -= t;
	return lifetime<=0;
}


