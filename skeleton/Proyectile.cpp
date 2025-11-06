#include "Proyectile.h"


Proyectile::Proyectile(Vector3D pos, Vector3D vel, float Mass, float Lifetime,float size): Particle(pos,vel,Mass,Lifetime,size)
{
}

Proyectile::~Proyectile()
{
}

void Proyectile::integrate(double t)
{
	
	Particle::integrate(t);

}



