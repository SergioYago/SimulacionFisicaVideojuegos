#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "Sphere.h"
#include "Vector3D.h"
#include "Proyectile.h"
#include "ParticleGenerator.h"
#include "GravityGenerator.h"
#include "GeneradorViento.h"
#include "Pelota.h"
#include "PelotaSystem.h"
#include "TorbellinoGenerator.h"
#include "ExplosionGenerator.h"
#include <iostream>

std::string display_text = "This is a test";


using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;
std::vector<std::unique_ptr< Proyectile>> proyectiles;

ParticleGenerator* pSystem;
GravityGenerator* gravityGen;
//ParticleSystem* pSystem;
PelotaSystem* pelotaSystem;
Pelota* pelota;
TorbellinoGenerator* torbellino;
GeneradorViento* windGen;
ParticleGenerator* generator;
ExplosionGenerator* explosion;
// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);
	stats particulaStat(10.f,1.f,{1,1,1,1});
	pelotaSystem = new PelotaSystem(20, Vector3D(3, 0, 3), Vector3D(0, 0, 0), Vector3D(2, 0, 2), Vector3D(0.f, 15.0f, 0), 0.75f, 0, 0, particulaStat);
	pelota =new Pelota(Vector3D{ 0,0,0 }, pelotaSystem,{ 50,50,0 }, { 0,0,5 }, 20, 99999999,5);
	windGen = new GeneradorViento(Vector3D{50,0,0});
	windGen->setActive(false);
	gravityGen = new GravityGenerator();
	pelotaSystem->AddForce(gravityGen);
	torbellino = new TorbellinoGenerator({ 0,0,0 },10, 200);
	generator = new ParticleGenerator(250, { 0,0,0 }, { 0,0,0 }, { 3,0,3 }, { 0,20,0 }, 5, 2, 0, particulaStat);
	explosion = new ExplosionGenerator({ 0,-5,0 }, 99999, 200, 2);
	generator->AddForce(torbellino);
	generator->AddForce(explosion);
	generator->AddForce(gravityGen);
	
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);
	gScene->simulate(t);
	gScene->fetchResults(true);
	generator->update(t);
	pelotaSystem->update(t);
	for (int  i = 0; i < proyectiles.size(); i++)
	{
		if (proyectiles[i]->canDestroy(t))
		{
			proyectiles.erase(proyectiles.begin() + i);
			
		}
		else
		{
			i++; 
		}
	}
	
	for (auto& aux: proyectiles) 
	{
		aux->AddForce(gravityGen->getForce(aux.get()));
		//aux->AddForce(torbellino->getForce(aux.get()));
		
		aux->integrate(t);
	}
	pelota->AddForce(gravityGen->getForce(pelota));
	pelota->AddForce(windGen->getForce(pelota));
	pelota->integrate(t);
	explosion->update(t);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();
	int aux = proyectiles.size();
	for(int i=0;i<aux;i++)
	{
		proyectiles.pop_back();
	}
	delete pelotaSystem;
	}
void shoot1()
{
	Vector3 aux= GetCamera()->getTransform().p;
	Vector3D pos = Vector3D(aux.x, aux.y, aux.z);
	aux= GetCamera()->getDir();
	Vector3D dir = Vector3D(aux.x, aux.y, aux.z);
	dir.normalized();
	
	//gs = gr(vs^2/vr^2)
	float gr = 9.81f * ((2.f * 2.f) / (25.f*25.f));
	
	pos += dir*3;

	proyectiles.push_back(std::make_unique<Proyectile>(pos, dir * 5,10, 10));
	
}
void shoot2()
{
	Vector3 aux = GetCamera()->getTransform().p;
	Vector3D pos = Vector3D(aux.x, aux.y, aux.z);
	aux = GetCamera()->getDir();
	Vector3D dir = Vector3D(aux.x, aux.y, aux.z);
	dir.normalized();
	Vector3D accel = { 0,0,0 };
	pos += dir*3;
	float gr = 9.81f * ((10.f * 10.f) / (25.f * 25.f));
	proyectiles.push_back(std::make_unique<Proyectile>(pos, dir * 5, 10, 10));
}
void shoot3()
{
	Vector3 aux = GetCamera()->getTransform().p;
	Vector3D pos = Vector3D(aux.x, aux.y, aux.z);
	aux = GetCamera()->getDir();
	Vector3D dir = Vector3D(aux.x, aux.y, aux.z);
	dir.normalized();
	pos += dir * 3;
	float gr = 9.81f * ((20.f * 20.f) / (25.f * 25.f));
	proyectiles.push_back(std::make_unique<Proyectile>(pos, dir * 5 ,10, 10));
}
// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	//case 'B': break;
	//case ' ':	break;
	case ' ':
	{

		break;
	}
	case'Q':
		shoot1();
		//pelota->changeSystem(2);
		break;
	case'E':
		explosion->Activate();
		cout<<"hola"<<endl;
		break;
	case'R':
		pelota->changeSystem(0);
		//shoot3();
		break;
	case'F':
		gravityGen->setActive(!gravityGen->isActive());
		break;
	case'G':
		torbellino->setActive(!torbellino->isActive());
		break;
	case'H':
		windGen->setActive(!windGen->isActive());
		break;
	case'C': {
		int randomNum = rand() % 5;
		randomNum++;
		if (windGen->getDir().x >= 0) { windGen->setDir({ (float)-randomNum ,0,0 }); }
		else { windGen->setDir({ (float)randomNum ,0,0 }); }
		break; }
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}
