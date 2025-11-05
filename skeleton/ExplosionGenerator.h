#pragma once
#include "GeneradorFuerza.h"
class ExplosionGenerator:public GeneradorFuerza
{
public:
	ExplosionGenerator(Vector3D pos,float fuerza,float rangeini,float rangend,float tim);
	Vector3D getForce(Particle* aux)override;
	void update(float t);
	~ExplosionGenerator();
private:
	Vector3D mPos;
	float rangeIni, rangeAct, rangeEnd, time, timAct = 0;
	float fuerzAct;
};

