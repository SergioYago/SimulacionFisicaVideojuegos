#include "ParticleSystem.h"


using namespace std;







ParticleSystem::ParticleSystem()
{
}

ParticleSystem::~ParticleSystem()
{
	int aux = particles.size();
	for (int i = 0; i < aux; i++)
	{
		particles[i].release();
	}
	for (auto it : fuerzas) { delete it; }
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


