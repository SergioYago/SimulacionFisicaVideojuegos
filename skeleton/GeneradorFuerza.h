#pragma once
#include "Vector3D.h"
#include "Particle.h"
#include "ParticleP.h"
class GeneradorFuerza
{
public:
	GeneradorFuerza(Vector3D Dir={0,0,0},float Force=0.f);
	~GeneradorFuerza();
	Vector3D getDir() { return dir; }
	void setDir(Vector3D newDir) { dir = newDir; dir.normalized(); }
	float getNumber() { return fuerza; }
	void setNumber(float newForce) { fuerza = newForce; }
	virtual Vector3D getForce(Particle* aux);
	virtual Vector3D getForce(ParticleP* aux);
	bool isActive(){ return active; }
	void setActive(bool b) { active = b; }
protected:
	Vector3D dir;
	float fuerza;
	bool active = true;
	
};

