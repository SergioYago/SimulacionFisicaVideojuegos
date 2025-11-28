#include "GravityGenerator.h"

GravityGenerator::GravityGenerator():GeneradorFuerza({0,-1,0},10.f )
{
}

GravityGenerator::~GravityGenerator()
{
}

Vector3D GravityGenerator::getForce(Particle* aux)
{
	Vector3D sol = { 0,0,0 };
	if (active) {//a siempre igual, así que a=F/m, siendo mass 1/m a =F*mass F=a/mass
		if (first) {
			sol.y -= (grav1 / aux->getMass());
		}
		else
		{
			sol.y -= (grav2 / aux->getMass());
		}
	}
	return sol;
}
Vector3D GravityGenerator::getForce(ParticleP* aux)
{
	Vector3D sol = { 0,0,0 };
	if (active) {//a siempre igual, así que a=F/m, siendo mass 1/m a =F*mass F=a/mass
		if (first) {
			sol.y -= (grav1 / aux->getMass());
		}
		else
		{
			sol.y -= (grav2 / aux->getMass());
		}
	}
	return sol;
}