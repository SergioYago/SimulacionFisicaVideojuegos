#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include "Vector3D.h"
using namespace physx;
constexpr float damping = 0.99999;
class Particle
{
public:
	Particle(Vector3D PosD, Vector3D Vel,float Mass, float Lifetime = 10.f);
	~Particle();
	virtual void integrate(double t);
	Vector3D getVel() { return vel; }
	Vector3D getPos() { return Vector3D(pos.p.x, pos.p.y, pos.p.z); }
	float getMass() { return mass; }
	void setVel(Vector3D v) { vel = v; }
	bool canDestroy(double t);
	void AddForce(Vector3D fuerza);
private:
	Vector3D vel=Vector3D(), accel=Vector3D();
	PxTransform pos;
	RenderItem* item;
	float lifetime, mass;
};

