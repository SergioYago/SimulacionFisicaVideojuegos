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
	Vector3D sol;
	sol = pos-aux->getPos();
	double num=sol.norm();
	if(num>=area)
	{
		sol = sol.normalized();
		sol = sol * fuerza;
	}
	return sol;
}
