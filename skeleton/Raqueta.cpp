#include "Raqueta.h"
#include <iostream>
using namespace std;
Raqueta::Raqueta(PxPhysics* gPhysics,PxScene* gScene)
{
	PxMaterial* material = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);
	tr.p = { 0,0,300 };
	tr.q = PxQuat(PxIdentity);
	body= gPhysics->createRigidStatic(tr);
	shape = body->createShape(PxBoxGeometry(30.0f, 30.0f, 2.f), *material);
	body->attachShape(*shape);
	shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
	
	Active = false;
	timeAct = 0;
	Scene = gScene;
	gScene->addActor(*body);
}

void Raqueta::integrate(double t)
{
	
	if (Active) {
		tr.p = GetCamera()->getEye();
		tr.p.z -= 10;
		body->setGlobalPose(tr);
		timeAct += t;
		if (timeAct >= timeActive)
		{
			deActivate();
		}
	}
	
}

void Raqueta::activate()
{
	shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, true);
	Scene->resetFiltering(*body);
	timeAct = 0;
	Active = true;
	std::cout << "abre" << endl;
	
}

void Raqueta::deActivate()
{
	shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
	Scene->resetFiltering(*body);
	Active = true;
}
