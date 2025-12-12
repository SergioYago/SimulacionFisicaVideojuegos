#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
using namespace physx;
class Raqueta
{
public:
	Raqueta(PxPhysics* gPhysics,PxScene* gScene);
	~Raqueta();
	PxRigidStatic* getActor() { return body; }
	void integrate(double t);
	void activate();
	void deActivate();
	bool isActive() { return Active; }
private:
	float timeActive=0.5f, timeAct;
	bool Active;
	PxShape* shape;
	PxRigidStatic* body;
	PxTransform tr;
	PxScene* Scene;
};

