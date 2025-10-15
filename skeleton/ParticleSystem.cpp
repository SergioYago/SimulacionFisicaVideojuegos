#include "ParticleSystem.h"
#include <stdlib.h> 
#include <random>
using namespace std;




ParticleSystem::ParticleSystem(int n, Vector3D pRange, Vector3D IniPos, Vector3D dRange, Vector3D IniDir, float initime, float timerange)
{
	nParticles = 0;
	maxParticles = n;
	posRange = pRange;
	iniPos = IniPos;
	dirRange = dRange;
	iniDir = IniDir;
	iniTime = initime;
	timeRange = timerange;
}

ParticleSystem::~ParticleSystem()
{
}
Vector3D ParticleSystem::generateRandom(Vector3D ini, Vector3D range)
{
	//tiene que hacerse por floats en vez de por vector
	std::default_random_engine gen;
	std::normal_distribution<float> distx(ini.x, range.x);
	std::normal_distribution<float> disty(ini.y, range.y);
	std::normal_distribution<float> distz(ini.z, range.z);
	Vector3D sol;
	sol.x = distx(gen);
	sol.y = disty(gen);
	sol.z = distz(gen);
	return sol;
}

void ParticleSystem::createParticle()
{
//mirar los rangos de posicion y pillar un random entre la inipos-posRange/2 y 
//inipos +posRange/2+1
	Vector3D pos;
	pos = generateRandom(iniPos, posRange);
	Vector3D dir;
	dir = generateRandom(iniDir, dirRange);
	
	std::default_random_engine gen;
	std::normal_distribution<float> dist(iniTime,timeRange);
	float lifetime = dist(gen);
	Vector3D accel = { 0,0,0 };
	proyectiles.push_back(std::make_unique<Particle>(pos, dir, accel, 0, 10));
}
void ParticleSystem::update(double t)
{
	if(nParticles<maxParticles)
	{
	
		for (nParticles = nParticles; nParticles < maxParticles; nParticles++)
		{
			createParticle();
		}
	}

	for (int i = 0; i < proyectiles.size(); i++)
	{
		if (proyectiles[i]->canDestroy(t))
		{
			proyectiles.erase(proyectiles.begin() + i);

		}
		else
		{
			i++;
		}
	}
	integrate(t);
}

void ParticleSystem::integrate(double t)
{
	for (auto& aux : proyectiles)
	{
		aux->integrate(t);
	}
}


