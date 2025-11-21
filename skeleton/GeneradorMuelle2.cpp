#include "GeneradorMuelle2.h"



GeneradorMuelle2::GeneradorMuelle2(float Force, float Area, Particle* other):GeneradorFuerza({0,0,0},Force)
{
	area = Area;
	aux2 = other;
}

GeneradorMuelle2::~GeneradorMuelle2()
{
}

Vector3D GeneradorMuelle2::getForce(Particle* aux)
{
	Vector3D dir, sol;

	dir = aux->getPos() - aux2->getPos();
	if (dir.x != 0 || dir.y != 0 || dir.z != 0) {
		sol = (dir / dir.norm()) * (-fuerza) * (dir.norm() - area);
	}
	return sol;
}
