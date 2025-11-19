#pragma once
#include "GeneradorFuerza.h"
class GeneradorMuelle1: public GeneradorFuerza
{
public:
	GeneradorMuelle1(Vector3D pos,float Force,float Area);
	~GeneradorMuelle1();
	Vector3D getForce(Particle* aux)override;
private:
	Vector3D pos;
	float area;
};

