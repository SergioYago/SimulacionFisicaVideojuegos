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
#include "GeneradorMuelle1.h"
#include "GeneradorMuelle2.h"
#include "Raqueta.h"
#include <iostream>

std::string display_text = "This is a test";

constexpr int AUDIENCIA = 6;
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
ProyectileP* Proyectilemuelle;
ParticleGenerator* pSystem;
GravityGenerator* gravityGen;
vector<pair<ProyectileP*, GeneradorMuelle1*>> audiencia;
PelotaSystem* pelotaSystem;
Pelota* pelota;
TorbellinoGenerator* torbellino1;
TorbellinoGenerator* torbellino2;
GeneradorViento* windGen;
ParticleGenerator* confeti1;
ParticleGenerator* confeti2;
ExplosionGenerator* explosion1;
ExplosionGenerator* explosion2;
PxRigidStatic* suelo;
PxRigidStatic* pared;
PxRigidStatic* pared2;
Raqueta* raq;
int counter;
bool juego_empieza = false;
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
	stats particulaStat(10.f,0.5f,{1,1,1,1});
	//creacion de la pelota
	pelotaSystem = new PelotaSystem(20, Vector3D(3, 0, 3), Vector3D(0, 0, 0), Vector3D(2, 0, 2), Vector3D(0.f, 15.0f, 0), 0.75f, 0, 0, particulaStat);
	pelota =new Pelota(pelotaSystem,{ 50,20,20 }, { 0,0,5 },gScene, 4, 99999999,3);
	particulaStat.size = 1.f;
	//creacion de generadores de fuerzas
	windGen = new GeneradorViento(Vector3D{50,0,0});
	windGen->setActive(false);
	gravityGen = new GravityGenerator();
	pelotaSystem->AddForce(gravityGen);
	torbellino1 = new TorbellinoGenerator({ -90,0,0 },10, 300);
	torbellino2 = new TorbellinoGenerator({ 180,0,0 },10, 300);
	explosion1 = new ExplosionGenerator({ -90,10,0 }, 99999, 200, 2);
	explosion2 = new ExplosionGenerator({ 180,10,0 }, 99999, 200, 2);
	//creación de los 2 generadores de partículas 
	confeti1 = new ParticleGenerator(200, { 0,0,0 }, { -90,0,0 }, { 3,0,3 }, { 0,20,0 }, 1,0.5f, 0, particulaStat,true);
	confeti2 = new ParticleGenerator(200, { 0,0,0 }, { 180,0,0 }, { 3,0,3 }, { 0,20,0 }, 1,0.5f, 0, particulaStat,true);
	//se les añaden las fuerzas
	confeti1->AddForce(torbellino1);
	confeti1->AddForce(explosion1);
	confeti1->AddForce(gravityGen);
	confeti2->AddForce(torbellino2);
	confeti2->AddForce(explosion2);
	confeti2->AddForce(gravityGen);
	//creación de pared y suelo
	PxTransform tr;
	tr.p = { 0,0,0 };
	tr.q = PxQuat(PxIdentity);
	PxMaterial* material = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);
	PxMaterial* material2 = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	PxShape* shape = CreateShape(PxBoxGeometry(100.0f, 0.5f, 140.0f),material);
	suelo=gPhysics->createRigidStatic(tr);
	gScene->addActor(*suelo);
	suelo->attachShape(*shape);
	suelo->setGlobalPose({50,0,50});
	RenderItem* item = new RenderItem(shape, suelo, { 0.9f,0.9f,0.9f,1 });
	PxShape* shape2 = CreateShape(PxBoxGeometry(100.0f, 100.0f, 0.5f),material);
	PxShape* shape3 = CreateShape(PxBoxGeometry(40.0f, 40.f, 0.5f),material);
	
	pared2=gPhysics->createRigidStatic(tr);
	gScene->addActor(*pared2);
	pared2->attachShape(*shape2);
	RenderItem* item3 = new RenderItem(shape2, pared2, { 0.9f,0.9f,0.9f,1 });
	pared2->setGlobalPose({ 50,50,-50 });
	//creación de la raqueta
	raq = new Raqueta(gPhysics, gScene);
	raq->activate();
	//para que empieze la pelota sin moverse del centro
	pelota->resetPos();
	//generación de la audiencia
	srand(time(0));
	int min = 13, max = 22;
	float posy = 0;
	float posx = -100;
	for (float i = 0; i < AUDIENCIA; i+=1) {
		//se generan de manera aleatoria para que parezca menos uniforme
		posy = min + (rand() % (max - min + 1));
		ProyectileP* aux= new ProyectileP({ posx,posy,-i*20.f+120.f }, { 0,0,0 }, gScene, 2, 99999, 4, { 1,0,0,1 },true);
		GeneradorMuelle1* aux2 = new GeneradorMuelle1({ posx,-20,-i * 20.f + 120.f }, 100, 30);
		audiencia.push_back({ aux,aux2 });
		
	}
	posx = 190;
	for (float i = 0; i < AUDIENCIA; i+=1) {
		while (posy >= 8 && posy <= 12)
		{
			posy = min + (rand() % (max - min + 1));
		}
		//si se pasa de 0 entonces se resetea
		ProyectileP* aux= new ProyectileP({posx,posy,-i*20.f+120.f }, { 0,0,0 }, gScene, 2, 99999, 4, { 1,0,0,1 },true);
		GeneradorMuelle1* aux2 = new GeneradorMuelle1({ posx,-20,-i * 20.f + 120.f }, 100, 30);
		audiencia.push_back({ aux,aux2 });
		posy = 10;
	}
	

}

void loose()
{
	GetCamera()->resetPos();
	pelota->resetPos();
	counter = 0;
	pelota->getActor()->clearForce(PxForceMode::eIMPULSE);
	pelota->getActor()->clearForce();
	pelota->getActor()->clearTorque();
	pelota->getActor()->clearTorque(PxForceMode::eIMPULSE);
	pelota->getActor()->setLinearVelocity({ 0,0,0 });
	juego_empieza = false;
}
// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);
	gScene->simulate(t);
	gScene->fetchResults(true);
	confeti1->update(t);
	confeti2->update(t);
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
	if (juego_empieza)
	{ 
		pelota->AddForce(gravityGen->getForce(pelota));
		pelota->AddForce(windGen->getForce(pelota));
	}
	
		

	pelota->integrate(t);
	explosion1->update(t);
	explosion2->update(t);
	raq->integrate(t);
	PxTransform pelotaTR = pelota->getActor()->getGlobalPose();
	if (pelotaTR.p.y < -10||pelotaTR.p.x>160||pelotaTR.p.x<-60||pelotaTR.p.z>200||pelotaTR.p.z<-60) { loose(); }
for(int i=0;i<audiencia.size();i++)
{
	audiencia[i].first->AddForce(audiencia[i].second->getForce(audiencia[i].first));
	audiencia[i].first->integrate(t);
}
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
		//if (GetCamera()->getEye().z >= pelota->getActor()->getGlobalPose().p.z + 3) {
			//haaaaaah?
			raq->activate();
		//}
		break;
	}
	case'R':
		loose();
		//pelota->changeSystem(2);
		break;
	case'E':
		explosion1->Activate();
		explosion2->Activate();
		break;
	case'F':
		gravityGen->setActive(!gravityGen->isActive());
		break;
	case'G':
		torbellino1->setActive(!torbellino1->isActive());
		torbellino2->setActive(!torbellino2->isActive());
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

	if(actor1==pelota->getActor())
	{
		if (actor2 == suelo) {
			pelota->changeSystem(0);
			counter++;
			if(counter>4)
			{
				loose();
			}
		}
		else if(actor2==raq->getActor())
		{
			if (raq->isActive()) {
				//aquí hay que hacer lo de la cámara
				auto aux = GetCamera()->getDir();
				aux.normalize();
				//multiplicamos el vector por una fuerza
				//y eso es lo que hay que pasarle a la pelota
				aux = aux * 100;
				aux.y += 100;
				aux.z -= 15;
				pelota->getActor()->clearForce(PxForceMode::eIMPULSE);
				pelota->getActor()->clearForce();
				pelota->getActor()->clearTorque();
				pelota->getActor()->clearTorque(PxForceMode::eIMPULSE);
				pelota->getActor()->addForce(aux, PxForceMode::eIMPULSE);
				pelota->changeSystem(2);
				
				raq->deActivate();
				juego_empieza = true;
				counter = 0;
			}
			
		}
		else if (actor2 == pared2)
		{
			pelota->changeSystem(1);
			counter = 0;
		}
	}

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
