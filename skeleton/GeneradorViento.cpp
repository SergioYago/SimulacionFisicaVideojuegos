#include "GeneradorViento.h"

GeneradorViento::GeneradorViento(Vector3D dir): GeneradorFuerza(dir.normalized(),dir.norm())
{
}
GeneradorViento::~GeneradorViento()
{
}

Vector3D GeneradorViento::getForce(Particle* aux)
{
	Vector3D force = { 0,0,0 };
	if (active) {
		if (dir.x != 0)
		{
			force.x = (dir.x * fuerza - aux->getVel().x) * k1;// +(dir * fuerza - aux->getVel()) * (dir * fuerza - aux->getVel()) * k2;ç
		}
		if (dir.y != 0) {
			force.y = (dir.y * fuerza - aux->getVel().y) * k1;// +(dir * fuerza - aux->getVel()) * (dir * fuerza - aux->getVel()) * k2;ç
		}
		if (dir.z != 0)
		{
			force.z = (dir.z * fuerza - aux->getVel().z) * k1;// +(dir * fuerza - aux->getVel()) * (dir * fuerza - aux->getVel()) * k2;ç
		}
	}
	return force;
}
