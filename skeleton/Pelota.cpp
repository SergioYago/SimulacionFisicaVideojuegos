#include "Pelota.h"


Pelota::Pelota( PelotaSystem* System, Vector3D pos, Vector3D dir, PxScene* gScene, float mass, float lifetime,float size): ProyectileP(pos,dir,gScene,mass,lifetime,size,{0,1,0,1})
{
	posIni = pos;
	system = System;
	msize = size;
	//bola->addForce({ 0,10,-50 }, PxForceMode::eIMPULSE);
}

Pelota::~Pelota()
{
	ParticleP::~ParticleP();
}

void Pelota::integrate(double t)
{
	ParticleP::integrate(t);
	Vector3D aux = getPos();
	
	//como compruebo esto?
	
	
}

void Pelota::changeSystemRange(Vector3D range)
{
	
}

void Pelota::changeSystemDir(Vector3D dir)
{
	system->updateDir(dir);
}

void Pelota::changeSystem(int n)
{
	Vector3D pos = getPos();
	Vector4 color = { 1,1,1,1 };
	Vector3D dirRange={0,0,0}, dirIni = {0,0,0}, posRange = {0,0,0};
	if(n==0)
	{
		pos.y -= ((msize/2)+1);
		dirRange = { 2,0,2 };
		dirIni = { 0,15,0 };
		posRange = { 1,0,1 };
		color = { 1,0,0,1 };
	}
	else if(n==1)
	{
	//delante de la bola con dir z positiva
		pos.z -= ((msize / 2) + 1);
		dirRange={ 2,7.5f,0 };
		dirIni = { 0,0,7.5 };
		posRange = { 1,1,0 };
		color = { 0,1,0,1 };
	}
	else
	{
	//detrás de la bola con z negativa
		pos.z += ((msize / 2) + 1);
		dirRange = { 2,7.5f,0 };
		dirIni = { 0,0,-7.5f };
		posRange = { 1,1,0 };
		color = { 0,0,1,1 };
		if(!empeiza)
		{
			empeiza = true;
			bola->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, false);
		}
	}
	system->updatePos(pos);
	system->updateposRange(posRange);
	system->updateDir(dirIni);
	system->updatedirRange(dirRange);
	system->setColor(color);
	system->Activate();
}

void Pelota::resetPos()
{
	bola->setGlobalPose({ posIni.x,posIni.y,posIni.z });
	bola->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
	empeiza = false;
}
