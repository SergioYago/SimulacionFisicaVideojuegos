#include "PelotaSystem.h"
PelotaSystem::PelotaSystem(int n, Vector3D pRange, Vector3D IniPos, Vector3D dRange, Vector3D IniDir, float initime, float timeRange, float yPendiente):ParticleSystem(n, pRange,IniPos,dRange,IniDir,initime,timeRange,yPendiente)
{

}
void PelotaSystem::update(double t)
{
	for (int i = 0; i < particles.size(); i++)
	{
		if (particles[i]->canDestroy(t))
		{
			particles.erase(particles.begin() + i);
			nParticles--;

		}
		else
		{
			i++;
		}
	}
	ParticleSystem::integrate(t);
}
PelotaSystem::~PelotaSystem()
{
	ParticleSystem::~ParticleSystem();
}

void PelotaSystem::Activate()
{
	for(int i=0;i<maxParticles;i++)
	{
		createParticle();
	}
}

void PelotaSystem::addOffsetPos(Vector3D offset)
{
	updatePos(getPos() + offset);
}

