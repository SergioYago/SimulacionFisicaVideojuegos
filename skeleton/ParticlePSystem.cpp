#include "ParticlePSystem.h"


using namespace std;







ParticlePSystem::ParticlePSystem()
{
}

ParticlePSystem::~ParticlePSystem()
{
	int aux = particles.size();
	for (int i = 0; i < aux; i++)
	{
		particles[i].release();
	}
	for (auto it : fuerzas) { delete it; }
}





void ParticlePSystem::AddForce(GeneradorFuerza* force)
{
	fuerzas.push_back(force);
}

void ParticlePSystem::integrate(double t)
{
	for (auto& aux : particles)
	{
		for (auto fuerza : fuerzas)
		{

			aux->AddForce(fuerza->getForce(aux.get()));
		}
		aux->integrate(t);
	}
}


