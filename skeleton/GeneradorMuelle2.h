#pragma once
#include "GeneradorFuerza.h"
class GeneradorMuelle2 : public GeneradorFuerza
{
public:
	GeneradorMuelle2(float Force, float Area,Particle* other1,ParticleP* other2);
	~GeneradorMuelle2();
	Vector3D getForce(Particle* aux)override;
	Vector3D getForce(ParticleP* aux)override;
private:
	float area;
	Particle* aux2=nullptr;
	ParticleP*aux3=nullptr;
};

