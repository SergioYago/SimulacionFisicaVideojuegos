#include "GeneradorViento.h"

GeneradorViento::GeneradorViento(Vector3D dir): GeneradorFuerza(dir)
{
}
GeneradorViento::~GeneradorViento()
{
}

Vector3D GeneradorViento::getForce(Particle* aux)
{
	Vector3D force = (dir * fuerza - aux->getVel()) * k1;// +(dir * fuerza - aux->getVel()) * (dir * fuerza - aux->getVel()) * k2;
	return force;
}
