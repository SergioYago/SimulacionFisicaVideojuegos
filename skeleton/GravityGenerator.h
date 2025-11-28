#pragma once
#include "GeneradorFuerza.h"
class GravityGenerator: public GeneradorFuerza
{
public:
	GravityGenerator();
	~GravityGenerator();
	Vector3D getForce(Particle* aux)override;
	Vector3D getForce(ParticleP* aux)override;
	void changeGrav() { first = !first; }
private:
	bool first = true;
	float grav1 = 9.81f;
	float grav2 = 9.81f/2;
};

