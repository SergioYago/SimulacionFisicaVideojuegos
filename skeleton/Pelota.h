#pragma once
#include "Particle.h"
#include "PelotaSystem.h"
class Pelota: public Particle
{
public:
	Pelota(Vector3D posfinal,PelotaSystem* System,Vector3D pos, Vector3D dir, Vector3D accel, float grav,float lifetime);
	~Pelota();
	virtual void integrate(double t) override;
private:
	Vector3D posFinal;
	PelotaSystem* system;
};

