#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include "Vector3D.h"
using namespace physx;
constexpr float damping = 0.99999;
struct stats
{
public:
	stats() { mass = 1.f; size = 1.f; }
	stats(float m, float s, Vector4 c)
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
	Vector3D getPos() { return Vector3D(pos.p.x, pos.p.y, pos.p.z); }
	float getMass() { return mass; }
	void setVel(Vector3D v) { vel = v; }
	bool canDestroy(double t);
	void AddForce(Vector3D fuerza);
private:
	Vector3D vel = Vector3D(), accel = Vector3D();
	PxTransform pos;
	RenderItem* item;
	float lifetime, mass;
};

