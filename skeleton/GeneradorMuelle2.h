#pragma once
#include "GeneradorFuerza.h"
class GeneradorMuelle2 : public GeneradorFuerza
{
public:
	GeneradorMuelle2(float Force, float Area,Particle* other);
	~GeneradorMuelle2();
	Vector3D getForce(Particle* aux)override;
private:
	float area;
	Particle* aux2;
};

