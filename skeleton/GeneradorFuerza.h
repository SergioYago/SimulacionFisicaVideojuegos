#pragma once
#include "Vector3D.h"
#include "Particle.h"
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
	bool isActive(){ return active; }
	void setActive(bool b) { active = b; }
protected:
	Vector3D dir;
	float fuerza;
	bool active = true;
	//viento:(Vv-Vp)*k1+|Vv-Vp|*(Vv-Vp)*k2. k1 y k2 cambian dependiendo de que tipo 
	// de viento 
	//en los torbellinos cambia dependiendo de la distancia a el 
	// (mayor cuanto mas lejos) y con la altura, menor al subir.
	//explosión se baja la fuerza con F=e^(t/tau) t =tiempo tau variable local
};

