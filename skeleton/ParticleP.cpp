#include "ParticleP.h"
#include <iostream>
#include <fstream>
#include <PxPhysicsAPI.h>

using namespace physx;
using namespace std;

ParticleP::ParticleP(Vector3D PosD, Vector3D Vel, PxScene* gScene, float Mass, float Lifetime, float size, Vector4 color, bool arcoiris)
{
	pos.p = { (float)PosD.x,(float)PosD.y,(float)PosD.z };
	pos.q = PxQuat(PxIdentity);
	PxPhysics* gPhysics = &PxGetPhysics();
	PxShape* shape = CreateShape(PxSphereGeometry(size));
	bola = gPhysics->createRigidDynamic(pos);
	bola->attachShape(*shape);
	gScene->addActor(*bola);
	vel = Vel;
	item = new RenderItem(shape, bola, color);
	bola->setMass(Mass);
	mass = 1 / Mass;
	lifetime = Lifetime;

	arcoIris = arcoiris;
	time = 0;
}

ParticleP::~ParticleP()
{
	item->release();
}

void ParticleP::integrate(double t)
{
	if(arcoIris)
	{
		time += t;
		float loop= fmod(time,9.f);
		Vector3 colorActual;
		if (loop < 3) {
			 colorActual= lerp({ 1,0,0 }, { 0,1,0 }, loop / 3);
		}
		else if(loop<6)
		{
			loop -= 3;
			colorActual = lerp({ 0,1,0 }, { 0,0,1 }, loop / 3.f);
		}
		else
		{
			loop -=6;
			colorActual = lerp({ 0,0,1 }, { 1,0,0 }, loop / 3.f);
		}
		item->color = { colorActual,1 };
	}
}

bool ParticleP::canDestroy(double t)
{
	lifetime -= t;
	return lifetime <= 0;
}

void ParticleP::AddForce(Vector3D fuerza)
{
		bola->addForce({fuerza.x,fuerza.y,fuerza.z});
}