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
	if(aux.z<posFinal.z)
	{
		changeSystem(1);
		Vector3D vel = getVel();
		vel.z =vel.z*-1;
		setVel(vel);
	}
	else if(aux.z > 30)
	{
		changeSystem(2);
		Vector3D vel = getVel();
		vel.z = vel.z * -1;
		setVel(vel );
	}
	if(aux.y<=30)
	{
		changeSystem(0);
		Vector3D vel = getVel();
		vel.y = 15;
		setVel(vel);
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
		dirIni = { 0,10,0 };
		posRange = { 2,0,2 };
	}
	else if(n==1)
	{
	//delante de la bola con dir z positiva
		pos.z -= msize/2;
		dirRange={ 2,7.5f,0 };
		dirIni = { 0,0,7.5 };
		posRange = { 2,2,0 };
	}
	else
	{
	//detrás de la bola con z negativa
		pos.z +=msize/2;
		dirRange = { 2,7.5f,0 };
		dirIni = { 0,0,-7.5f };
		posRange = { 2,2,0 };

	}
	system->updatePos(pos);
	system->updateposRange(posRange);
	system->updateDir(dirIni);
	system->updatedirRange(dirRange);
	system->Activate();
}
