#include "ExplosionGenerator.h"
#include <cmath>
ExplosionGenerator::ExplosionGenerator(Vector3D pos, float fuerza, float Range, float tim):GeneradorFuerza({0,0,0},fuerza)
{
	mPos = pos;
	range = Range;
	time = tim;
	active = false;
}

Vector3D ExplosionGenerator::getForce(Particle* aux)
{
    
        Vector3D pos = aux->getPos();
        mPos;
        Vector3D vector = pos - mPos;
         if (( range>=vector.norm())&&active) {
             
             float powerF = fuerza / ((vector.norm()*vector.norm()));
            float dT = ((time-timAct) / time);
            float timeF = powf(exp(1.0), -dT);

            float rX = powerF * (vector.x)*timeF;
            float rY = powerF * (vector.y)*timeF;
            float rZ = powerF * (vector.z)*timeF;

            Vector3D result = { rX, rY, rZ };
            return result;
        }
        else return { 0,0,0 };
    
}

Vector3D ExplosionGenerator::getForce(ParticleP* aux)
{
    Vector3D pos = aux->getPos();
    mPos;
    Vector3D vector = pos - mPos;
    if ((range >= vector.norm()) && active) {

        float powerF = fuerza / ((vector.norm() * vector.norm()));
        float dT = ((time - timAct) / time);
        float timeF = powf(exp(1.0), -dT);

        float rX = powerF * (vector.x) * timeF;
        float rY = powerF * (vector.y) * timeF;
        float rZ = powerF * (vector.z) * timeF;

        Vector3D result = { rX, rY, rZ };
        return result;
    }
    else return { 0,0,0 };

}

void ExplosionGenerator::update(float t)
{
	//cuando timAct == 0 fuerza=0 tengo que ir restando con respecto a timAct
	if (active) {
		timAct -= t;
		if (timAct <= 0) { active = false; }
	}
}

void ExplosionGenerator::Activate()
{
	active = true; timAct = time;
}

ExplosionGenerator::~ExplosionGenerator()
{
}
