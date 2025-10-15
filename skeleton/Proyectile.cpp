#include "Proyectile.h"
Proyectile::Proyectile(Vector3D pos,Vector3D vel, Vector3D Accel, float Mass,float g,float live):Particle(pos, vel, Accel,g,live)
{
	mass = Mass;
	
}

void Proyectile::integrate(double t)
{
	
	Particle::integrate(t);

}



