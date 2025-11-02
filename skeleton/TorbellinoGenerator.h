#pragma once
#include "GeneradorFuerza.h"
class TorbellinoGenerator: public GeneradorFuerza
{
public:
	TorbellinoGenerator(Vector3D pos,float fuerza, float radioEfecto );
	~TorbellinoGenerator();
	Vector3D getForce(Particle* aux)override;
private:
	Vector3D mPos;
	float mRadio;
};

