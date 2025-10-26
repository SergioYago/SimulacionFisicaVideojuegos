#pragma once
#include "ParticleSystem.h"
class PelotaSystem:public ParticleSystem
{
public:
	PelotaSystem(int n, Vector3D pRange, Vector3D IniPos, Vector3D dRange, Vector3D IniDir, float initime, float timeRange, float yPendiente = 0.f,float grav =0.f);
	void update(double t) override;
	~PelotaSystem();
	void Activate();
};

