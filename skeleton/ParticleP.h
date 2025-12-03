#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include "Vector3D.h"
using namespace physx;
struct stats2
{
public:
	stats2() { mass = 1.f; size = 1.f; }
	stats2(float m, float s, Vector4 c)
	{
		mass = m; size = s; color = c;
	}
	float mass, size;
	Vector4 color = { 1,1,1,1 };
};
class ParticleP
{
public:
	ParticleP(Vector3D PosD, Vector3D Vel, PxScene* gScene, float Mass, float Lifetime = 10.f, float size = 1.f, Vector4 color = { 1,1,1,1 });
	~ParticleP();
	virtual void integrate(double t);
	Vector3D getVel() { return vel; }
	Vector3D getPos() { auto aux = bola->getGlobalPose().p; return Vector3D(aux.x,aux.y,aux.z); }
	float getMass() { return mass; }
	void setVel(Vector3D v) { vel = v; }
	bool canDestroy(double t);
	void AddForce(Vector3D fuerza);
private:
	Vector3D vel = Vector3D(), accel = Vector3D();
	PxTransform pos;
	RenderItem* item;
	float lifetime, mass;
	
protected:
	PxRigidDynamic* bola;
};

