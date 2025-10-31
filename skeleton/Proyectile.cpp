#include "Proyectile.h"


Proyectile::Proyectile(Vector3D pos, Vector3D vel, float Mass, float Lifetime): Particle(pos,vel,Mass,Lifetime)
{
}

void Proyectile::integrate(double t)
{
	
	Particle::integrate(t);

}



