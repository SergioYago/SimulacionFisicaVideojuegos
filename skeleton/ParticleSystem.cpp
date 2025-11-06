#include "ParticleSystem.h"


using namespace std;







ParticleSystem::ParticleSystem()
{
}

ParticleSystem::~ParticleSystem()
{
}





void ParticleSystem::AddForce(GeneradorFuerza* force)
{
	fuerzas.push_back(force);
}

void ParticleSystem::integrate(double t)
{
	for (auto& aux : particles)
	{
		for(auto fuerza:fuerzas)
		{
			
			aux->AddForce(fuerza->getForce(aux.get()));
		}
		aux->integrate(t);
	}
}


