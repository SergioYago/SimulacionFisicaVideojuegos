#pragma once
#include "ParticleP.h"

class ProyectileP : public ParticleP
{
public:
	ProyectileP(Vector3D pos, Vector3D vel, PxScene* gScene, float Mass = 0.01, float Lifetime = 10, float size = 1.0f,Vector4 color={1,1,1,1});
	~ProyectileP();
	virtual void integrate(double t) override;
};

