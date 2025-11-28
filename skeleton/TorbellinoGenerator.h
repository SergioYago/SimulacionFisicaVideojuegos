#pragma once
#include "GeneradorFuerza.h"
class TorbellinoGenerator: public GeneradorFuerza
{
public:
	TorbellinoGenerator(Vector3D pos,float fuerza, float radioEfecto );
	~TorbellinoGenerator();
	Vector3D getForce(Particle* aux)override;
	Vector3D getForce(ParticleP* aux)override;
private:
	Vector3D mPos;
	float mRadio;
	float k1 = 1.f;
};

