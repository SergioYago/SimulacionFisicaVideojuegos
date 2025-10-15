#pragma once
#include "Particle.h"

class Proyectile: public Particle
{
public:
	Proyectile(Vector3D pos, Vector3D vel, Vector3D Accel = Vector3D({ 0,0,0 }), float Mass = 0.01, float grav = 9., float Lifetime = 10);
	virtual void integrate(double t) override;
	
	
private:
	float mass;
	
};

