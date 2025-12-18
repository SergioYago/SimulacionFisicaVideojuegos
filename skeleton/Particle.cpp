#include "Particle.h"
#include <iostream>
#include <fstream>


Particle::Particle(Vector3D PosD, Vector3D Vel, float Mass, float Lifetime, float size, Vector4 color,bool arcoiris)
{
	pos.p = { (float)PosD.x,(float)PosD.y,(float)PosD.z };
	pos.q = { 0,0,0,0 };
	vel = Vel;
	item = new RenderItem(CreateShape(PxSphereGeometry(size)), &pos, color);
	mass = 1 / Mass;
	lifetime = Lifetime;
	arcoIris = arcoiris;
	time = 0;
}

Particle::~Particle()
{
	item->release();	
}

void Particle::integrate(double t)
{
	pos.p.x+=vel.x*t;
	pos.p.y+=vel.y*t;
	pos.p.z+=vel.z*t;
	vel += accel * t;
	vel =vel* pow(damping, t);
	accel = { 0,0,0 };
	if (arcoIris)
	{
		time += t;
		float loop = fmod(time, 9.f);
		Vector3 colorActual;
		if (loop < 3) {
			colorActual = lerp({ 1,0,0 }, { 0,1,0 }, loop / 3);
		}
		else if (loop < 6)
		{
			loop -= 3;
			colorActual = lerp({ 0,1,0 }, { 0,0,1 }, loop / 3.f);
		}
		else
		{
			loop -= 6;
			colorActual = lerp({ 0,0,1 }, { 1,0,0 }, loop / 3.f);
		}
		item->color = { colorActual,1 };
	}
}

bool Particle::canDestroy(double t)
{
	lifetime -= t;
	return lifetime<=0;
}

void Particle::AddForce(Vector3D fuerza)
{
	accel += fuerza*mass;
}