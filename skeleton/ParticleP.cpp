#include "ParticleP.h"
#include <iostream>
#include <fstream>
#include <PxPhysicsAPI.h>

using namespace physx;

ParticleP::ParticleP(Vector3D PosD, Vector3D Vel, PxScene* gScene, float Mass, float Lifetime, float size, Vector4 color)
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
	mass = 1 / Mass;
	lifetime = Lifetime;

}

ParticleP::~ParticleP()
{
	item->release();
}

void ParticleP::integrate(double t)
{
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