#pragma once
#include "Particle.h"
#include "GeneradorFuerza.h"
#include <vector>
#include <random>
#include <stdlib.h> 
using namespace std;
class ParticleSystem
{
public:
	ParticleSystem(int n,Vector3D pRange, Vector3D IniPos,Vector3D dRange,Vector3D IniDir,float initime,float timeRange, float yPendiente=0.f);
	~ParticleSystem();
	virtual void update(double t);
	void updatePos(Vector3D newPos) { iniPos = newPos; }
	void updateDir(Vector3D newDir) { iniDir = newDir; }
	Vector3D getPos() { return iniPos; }
protected:
	std::vector<std::unique_ptr< Particle>> particles;
	int nParticles, maxParticles;
	void integrate(double t);
	void createParticle();
private:
	
	
	Vector3D iniPos, posRange, iniDir,dirRange;
	float timeRange, iniTime;
	std::normal_distribution<float> dist;
	Vector3D generateRandom(Vector3D ini,Vector3D range);
	std::vector<GeneradorFuerza*> fuerzas;
	static std::default_random_engine gen;
	float yPendiente;
};

