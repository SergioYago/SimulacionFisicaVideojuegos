#pragma once
#include "GeneradorFuerza.h"
class ExplosionGenerator:public GeneradorFuerza
{
public:
	ExplosionGenerator(Vector3D pos,float fuerza,float range,float tim);
	Vector3D getForce(Particle* aux)override;
	Vector3D getForce(ParticleP* aux)override;
	void update(float t);
	void Activate();
	~ExplosionGenerator();
private:
	Vector3D mPos;
	float range, time, timAct = 0;
};

