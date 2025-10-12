#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include "Vector3D.h"
using namespace physx;
constexpr float damping = 0.99999;
class Particle
{
public:
	Particle(Vector3D PosD, Vector3D Vel,Vector3D Accel=Vector3D({0,0,0}));
	~Particle();
	virtual void integrate(double t);
	Vector3D getVel() { return vel; }
	void setVel(Vector3D v = Vector3D({ 0,0,0 })) { vel = v; }
	
private:
	Vector3D vel, accel;
	PxTransform pos;
	RenderItem* item;
	
};

