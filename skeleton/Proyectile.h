#pragma once
#include "Particle.h"

class Proyectile: public Particle
{
public:
	Proyectile(Vector3D pos, Vector3D vel, float Mass = 0.01, float Lifetime = 10);
	virtual void integrate(double t) override;
};

