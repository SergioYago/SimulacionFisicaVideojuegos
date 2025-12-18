#include "ProyectileP.h"


ProyectileP::ProyectileP(Vector3D pos, Vector3D vel, PxScene* gScene, float Mass, float Lifetime, float size, Vector4 color,bool arcoiris) : ParticleP(pos, vel, gScene, Mass, Lifetime, size, color,arcoiris)
{
}

ProyectileP::~ProyectileP()
{
}

void ProyectileP::integrate(double t)
{

	ParticleP::integrate(t);

}



