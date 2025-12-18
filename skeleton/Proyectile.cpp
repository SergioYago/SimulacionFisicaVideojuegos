#include "Proyectile.h"


Proyectile::Proyectile(Vector3D pos, Vector3D vel, float Mass, float Lifetime,float size,bool arcoiris): Particle(pos,vel,Mass,Lifetime,size,Vector4(1,1,1,1), arcoiris)
{
}

Proyectile::~Proyectile()
{
}

void Proyectile::integrate(double t)
{
	
	Particle::integrate(t);

}



