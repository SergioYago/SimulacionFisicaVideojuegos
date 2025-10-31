#include "GeneradorFuerza.h"

GeneradorFuerza::GeneradorFuerza(Vector3D Dir, float Force)
{
	dir = Dir;
	fuerza = Force;
}

GeneradorFuerza::~GeneradorFuerza()
{
}

Vector3D GeneradorFuerza::getForce(Particle* aux)
{
	Vector3D sol = { 0,0,0 };
	if (active)
	{
		sol = dir * fuerza;
	}
	return sol;
}




