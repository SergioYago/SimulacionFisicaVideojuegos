#include "Pelota.h"


Pelota::Pelota(Vector3D posfinal, PelotaSystem* System, Vector3D pos, Vector3D dir, float mass, float lifetime,float size): Proyectile(pos,dir,mass,lifetime,size)
{
	posFinal = posfinal;
	system = System;
	msize = size;
}

Pelota::~Pelota()
{
	Particle::~Particle();
}

void Pelota::integrate(double t)
{
	Particle::integrate(t);
	Vector3D aux = getPos();
	//como compruebo esto?
	if(aux.x<posFinal.x||aux.y>posFinal.y||aux.z>posFinal.z)
	{
		system->updatePos(getPos());
		system->Activate();
	}
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
	Vector3D dirRange={0,0,0}, dirIni = {0,0,0}, posRange = {0,0,0};
	if(n==0)
	{
		pos.y -= msize/2;
		dirRange = { 2,0,2 };
		dirIni = { 0,15,0 };
		posRange = { 3,0,3 };
	}
	else if(n==1)
	{
	//delante de la bola con dir z positiva
		pos.z -= msize/2;
		dirRange={ 2,10,0 };
		dirIni = { 0,0,15 };
		posRange = { 3,3,0 };
	}
	else
	{
	//detrás de la bola con z negativa
		pos.z +=msize/2;
		dirRange = { 2,10,0 };
		dirIni = { 0,0,-15 };
		posRange = { 3,3,0 };

	}
	system->updatePos(pos);
	system->updateposRange(posRange);
	system->updateDir(dirIni);
	system->updatedirRange(dirRange);
	system->Activate();
}
