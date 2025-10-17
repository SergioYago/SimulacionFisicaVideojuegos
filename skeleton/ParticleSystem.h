#pragma once
#include "Particle.h"
#include <vector>
#include <random>
#include <stdlib.h> 
using namespace std;
class ParticleSystem
{
public:
	ParticleSystem(int n,Vector3D pRange, Vector3D IniPos,Vector3D dRange,Vector3D IniDir,float initime,float timeRange, float yPendiente=0.f);
	~ParticleSystem();
	void update(double t);
private:
	
	int nParticles,maxParticles;
	Vector3D iniPos, posRange, iniDir,dirRange;
	float timeRange, iniTime;
	std::vector<std::unique_ptr< Particle>> particles;
	void integrate(double t);
	Vector3D generateRandom(Vector3D ini,Vector3D range);
	void createParticle();
	static std::default_random_engine gen;
	float yPendiente;
};

