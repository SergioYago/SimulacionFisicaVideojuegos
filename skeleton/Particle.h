#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
using namespace physx;
constexpr float damping = 0.99999;
class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel,Vector3 Accel={0,0,0});
	~Particle();
	void integrate(double t);
	
private:
	Vector3 vel, accel;
	PxTransform pos;
	RenderItem* item;
	
};

