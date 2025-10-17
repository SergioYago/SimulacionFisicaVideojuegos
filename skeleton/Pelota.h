#pragma once
#include "Particle.h"
#include "ParticleSystem.h"
class Pelota: public Particle
{
public:
	Pelota(Vector3D posfinal,ParticleSystem* System,Vector3D pos, Vector3D dir, Vector3D accel, float grav,float lifetime);
	~Pelota();
	virtual void integrate(double t) override;
private:
	Vector3D posFinal;
	ParticleSystem* system;
};

