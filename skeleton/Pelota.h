#pragma once
#include "Proyectile.h"
#include "PelotaSystem.h"
class Pelota: public Proyectile
{
public:
	Pelota(Vector3D posfinal,PelotaSystem* System,Vector3D pos, Vector3D dir,float mass,float lifetime);
	~Pelota();
	virtual void integrate(double t) override;
private:
	Vector3D posFinal;
	PelotaSystem* system;
};

