#pragma once
#include "ParticleSystem.h"
class ParticlePGenerator : public ParticleSystem
{
public:
	ParticlePGenerator(int n, Vector3D pRange, Vector3D IniPos, Vector3D dRange, Vector3D IniDir, float initime, float timeRange, float yPendiente, stats ParticulaB, PxScene* gScene);
	~ParticlePGenerator();
	virtual void update(double t);
	void updatePos(Vector3D newPos) { iniPos = newPos; };
	void updateDir(Vector3D newDir) { iniDir = newDir; };
	void updateposRange(Vector3D newRange) { posRange = newRange; };
	void updatedirRange(Vector3D newRange) { dirRange = newRange; };
	void setColor(Vector4 Color) { particulaB.color = Color; }
	Vector3D getPos() { return iniPos; }
protected:
	int nParticles, maxParticles;
	void createParticle();
	PxScene* gScene;
private:

	Vector3D generateRandom(Vector3D ini, Vector3D range);
	Vector3D iniPos, posRange, iniDir, dirRange;
	float timeRange, iniTime;
	std::normal_distribution<float> dist;
	static std::default_random_engine gen;
	stats particulaB;
	float yPendiente;
};

