#include "GeneradorMuelle1.h"

GeneradorMuelle1::GeneradorMuelle1(Vector3D Pos, float Force, float Area):GeneradorFuerza({0,0,0},Force)
{
	pos = Pos;
	area = Area;
}

GeneradorMuelle1::~GeneradorMuelle1()
{
}

Vector3D GeneradorMuelle1::getForce(Particle* aux)
{
	Vector3D dir,sol;
	
	dir =aux->getPos()-pos;
	if (dir.x != 0 || dir.y != 0 || dir.z != 0) {
		sol = (dir / dir.norm()) * (-fuerza) * (dir.norm() - area);
	}
	return sol;
}
Vector3D GeneradorMuelle1::getForce(ParticleP* aux)
{
	Vector3D dir,sol;
	
	dir =aux->getPos()-pos;
	if (dir.x != 0 || dir.y != 0 || dir.z != 0) {
		sol = (dir / dir.norm()) * (-fuerza) * (dir.norm() - area);
	}
	return sol;
}
