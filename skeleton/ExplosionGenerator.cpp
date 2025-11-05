#include "ExplosionGenerator.h"

ExplosionGenerator::ExplosionGenerator(Vector3D pos, float fuerza, float rangeini, float rangend, float tim):GeneradorFuerza({0,0,0},fuerza)
{
	mPos = pos;
	rangeIni = rangeini;
	rangeAct = rangeIni;
	rangeEnd = rangend;
	time = tim;
	fuerzAct = fuerza;
}

Vector3D ExplosionGenerator::getForce(Particle* aux)
{
	Vector3D pos = aux->getPos();
	pos =pos- mPos;
	if(active&&pos.norm()<=rangeAct)
	{
	
	}
}

void ExplosionGenerator::update(float t)
{
	//cuando timAct == 0 fuerza=0 tengo que ir restando con respecto a timAct
	if (active) {
		timAct -= t;
		if (timAct <= 0) { active = false; }

	}
}

ExplosionGenerator::~ExplosionGenerator()
{
}
