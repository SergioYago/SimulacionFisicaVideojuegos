#include "ProyectileP.h"


ProyectileP::ProyectileP(Vector3D pos, Vector3D vel, PxScene* gScene, float Mass, float Lifetime, float size, Vector4 color) : ParticleP(pos, vel, gScene, Mass, Lifetime, size, color)
{
}

ProyectileP::~ProyectileP()
{
}

void ProyectileP::integrate(double t)
{

	ParticleP::integrate(t);

}



