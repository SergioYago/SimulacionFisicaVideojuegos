#include "ProyectileP.h"


ProyectileP::ProyectileP(Vector3D pos, Vector3D vel, PxScene* gScene, float Mass, float Lifetime, float size) : ParticleP(pos, vel, gScene, Mass, Lifetime, size)
{
}

ProyectileP::~ProyectileP()
{
}

void ProyectileP::integrate(double t)
{

	ParticleP::integrate(t);

}



