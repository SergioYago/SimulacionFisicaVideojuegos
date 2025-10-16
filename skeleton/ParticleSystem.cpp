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
    static std::default_random_engine gen(std::random_device{}());
	std::normal_distribution<float> distx(100.f, 0.1f);
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
	if (posRange.x > 0.f&&posRange.y>0.f&&posRange.z>0.f) {
		pos = generateRandom(iniPos, posRange);
	}
	else { pos = iniPos; }
	Vector3D dir;
	if (dirRange.x > 0.f && dirRange.y > 0.f && dirRange.z > 0.f) {
		dir = generateRandom(iniDir, dirRange);
	}
	else { dir = iniDir; }
	float lifetime;
	if (timeRange > 0.f) {
		static std::default_random_engine gen(std::random_device{}());
		std::normal_distribution<float> dist(iniTime, timeRange);
		lifetime = dist(gen);
	}
	else { lifetime = iniTime; }
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
			nParticles--;

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


