#pragma once
#include "ParticleGenerator.h"
class PelotaSystem:public ParticleGenerator
{
public:
	PelotaSystem(int n, Vector3D pRange, Vector3D IniPos, Vector3D dRange, Vector3D IniDir, float initime, float timeRange, float yPendiente = 0.f);
	void update(double t) override;
	~PelotaSystem();
	void Activate();
	void addOffsetPos(Vector3D offset);
};

