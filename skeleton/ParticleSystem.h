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
	ParticleSystem();
	~ParticleSystem();
	
	void AddForce(GeneradorFuerza* force);
protected:
	std::vector<std::unique_ptr< Particle>> particles;
	void integrate(double t);

private:

	std::vector<GeneradorFuerza*> fuerzas;

};

