#pragma once
#include "ProyectileP.h"
#include "PelotaSystem.h"
class Pelota: public ProyectileP
{
public:
	Pelota(PelotaSystem* System,Vector3D pos, Vector3D dir, PxScene* gScene,float mass,float lifetime,float size);
	~Pelota();
	virtual void integrate(double t) override;
	void changeSystemRange(Vector3D range);
	void changeSystemDir(Vector3D dir);
	void changeSystem(int n);
	void resetPos();
private:
	Vector3D posIni;
	PelotaSystem* system;
	float msize;
	bool empeiza = false;
};

