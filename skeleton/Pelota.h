#pragma once
#include "Proyectile.h"
#include "PelotaSystem.h"
class Pelota: public Proyectile
{
public:
	Pelota(Vector3D posfinal,PelotaSystem* System,Vector3D pos, Vector3D dir,float mass,float lifetime,float size);
	~Pelota();
	virtual void integrate(double t) override;
	void changeSystemRange(Vector3D range);
	void changeSystemDir(Vector3D dir);
	void changeSystem(int n);
private:
	Vector3D posFinal;
	PelotaSystem* system;
	float msize;
};

