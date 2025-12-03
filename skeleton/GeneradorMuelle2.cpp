#include "GeneradorMuelle2.h"





GeneradorMuelle2::GeneradorMuelle2(float Force, float Area, Particle* other1, ParticleP* other2)
{
	area = Area;
	
	aux2 = other1;
	aux3 = other2;
}

GeneradorMuelle2::~GeneradorMuelle2()
{
}

Vector3D GeneradorMuelle2::getForce(Particle* aux)
{
	Vector3D dir, sol;
	if (aux2 != nullptr) {
		dir = aux->getPos() - aux2->getPos();
		if (dir.x != 0 || dir.y != 0 || dir.z != 0) {
			sol = (dir / dir.norm()) * (-fuerza) * (dir.norm() - area);
		}
	}
	else if (aux3 != nullptr) {
		dir = aux->getPos() - aux3->getPos();
		if (dir.x != 0 || dir.y != 0 || dir.z != 0) {
			sol = (dir / dir.norm()) * (-fuerza) * (dir.norm() - area);
		}
	}
	return sol;
}
Vector3D GeneradorMuelle2::getForce(ParticleP* aux)
{
	Vector3D dir, sol;
	if (aux2 != nullptr) {
		dir = aux->getPos() - aux2->getPos();
		if (dir.x != 0 || dir.y != 0 || dir.z != 0) {
			sol = (dir / dir.norm()) * (-fuerza) * (dir.norm() - area);
		}
	}
	else if (aux3 != nullptr) {
		dir = aux->getPos() - aux3->getPos();
		if (dir.x != 0 || dir.y != 0 || dir.z != 0) {
			sol = (dir / dir.norm()) * (-fuerza) * (dir.norm() - area);
		}
	}
	return sol;
}
