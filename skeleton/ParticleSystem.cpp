#include "ParticleSystem.h"
#include <stdlib.h> 
#include <random>
using namespace std;


ParticleSystem::ParticleSystem(int n, Vector3D pRange, Vector3D IniPos, Vector3D dRange, Vector3D IniDir)
{
	nParticles = 0;
	maxParticles = n;
	posRange = pRange;
	iniPos = IniPos;
	dirRange = dRange;
	iniDir = IniDir;
}

ParticleSystem::~ParticleSystem()
{
}
Vector3D ParticleSystem::generateRandom(Vector3D ini, Vector3D range)
{
	Vector3D sol = { 0,0,0 };
	int aux1 = ini.x - (range.x / 2);
	int aux2 = ini.x + (range.x / 2);
	sol.x = aux1 + static_cast<float> (rand() / (static_cast<float>(RAND_MAX / aux2)));
	int aux1 = ini.y - (range.y / 2);
	int aux2 = ini.y + (range.y / 2);
	sol.y = aux1 + static_cast<float> (rand() / (static_cast<float>(RAND_MAX / aux2)));
	int aux1 = ini.z - (range.z / 2);
	int aux2 = ini.z + (range.z / 2);
	sol.z = aux1 + static_cast<float> (rand() / (static_cast<float>(RAND_MAX / aux2)));
	return sol;
//	std::normal_distribution
}

void ParticleSystem::createParticle()
{
//mirar los rangos de posicion y pillar un random entre la inipos-posRange/2 y 
//inipos +posRange/2+1
	Vector3D pos;
	int aux1 = iniPos.x - (posRange.x / 2);
	int aux2 = iniPos.x + (posRange.x / 2);
	pos.x = rand() % aux1 + aux2;
	aux1 = iniPos.y - (posRange.y / 2);
	aux2 = iniPos.y + (posRange.y / 2);
	pos.y = rand() % aux1 + aux2;
	aux1 = iniPos.z - (posRange.z / 2);
	aux2 = iniPos.z + (posRange.z / 2);
	pos.z = rand() % aux1 + aux2;
	//ahora toca el tiempo de vida y la direccion
	Vector3D dir;
	aux1 = iniDir.x - (dirRange.x / 2);
	int aux2 = iniPos.x + (posRange.x / 2);
	pos.x = rand() % aux1 + aux2;
	aux1 = iniPos.y - (posRange.y / 2);
	aux2 = iniPos.y + (posRange.y / 2);
	pos.y = rand() % aux1 + aux2;
	aux1 = iniPos.z - (posRange.z / 2);
	aux2 = iniPos.z + (posRange.z / 2);
	pos.z = rand() % aux1 + aux2;
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


