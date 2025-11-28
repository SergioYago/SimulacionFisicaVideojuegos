#pragma once
#include "ParticleP.h"
#include "GeneradorFuerza.h"
#include <vector>
#include <random>
#include <stdlib.h> 
using namespace std;
class ParticlePSystem
{
public:
	ParticlePSystem();
	~ParticlePSystem();

	void AddForce(GeneradorFuerza* force);
protected:
	std::vector<std::unique_ptr<ParticleP>> particles;
	void integrate(double t);

private:

	std::vector<GeneradorFuerza*> fuerzas;

};

