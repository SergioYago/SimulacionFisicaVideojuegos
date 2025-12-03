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
	pos.p.x += vel.x * t;
	pos.p.y += vel.y * t;
	pos.p.z += vel.z * t;
	
	bola->addForce({(float)(accel.x*t),(float)(accel.y*t),(float)(accel.z*t)});
	accel = { 0,0,0 };

}

bool ParticleP::canDestroy(double t)
{
	lifetime -= t;
	return lifetime <= 0;
}

void ParticleP::AddForce(Vector3D fuerza)
{
	accel += fuerza * mass;
}