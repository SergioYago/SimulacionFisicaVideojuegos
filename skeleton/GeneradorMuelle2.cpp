#include "GeneradorMuelle2.h"

GeneradorMuelle2::GeneradorMuelle2(float Force, float Area):GeneradorFuerza({0,0,0},Force)
{
	area = Area;
}

GeneradorMuelle2::~GeneradorMuelle2()
{
}

Vector3D GeneradorMuelle2::getForce(Particle* aux)
{
	return Vector3D();
}
