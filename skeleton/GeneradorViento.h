#pragma once
#include "GeneradorFuerza.h"
class GeneradorViento : public GeneradorFuerza
{
public:
	GeneradorViento(Vector3D dir);
	~GeneradorViento();
	Vector3D getForce(Particle* aux)override;
	Vector3D getForce(ParticleP* aux)override;
private:
	float k1=1,k2=0;
};

