#pragma once
#include "Particle.h"
#include <vector>
using namespace std;
class ParticleSystem
{
public:
	ParticleSystem(int n,Vector3D pRange={0,0,0}, Vector3D IniPos={0,0,0},Vector3D dRange={0,0,0},Vector3D IniDir);
	~ParticleSystem();
	void update(double t);
private:
	//necestio 3 rangos, posicion,
	//dirección (velocidad y gravedad) y tiempo de vida
	//el rango de pos puede ser 0
	//el tiempo de vida supongo que no puede ser 0 porque entonces no se debreia ni crear
	//dirección puede ser 0
	//podemos usar lo de la gravedad? formula esa para gravedad simulada en main.cpp
	//primero genero, luego hago el update para ver si elimino, luego elimino las que hay que quitar,
	//sigo con moviendo las particulas y luego que se representen
	//Numero de particulas actual y el numero maximo de particulas
	int nParticles,maxParticles;
	Vector3D iniPos, posRange, iniDir,dirRange;
	int timeRange;
	std::vector<std::unique_ptr< Particle>> proyectiles;
	void integrate(double t);
	Vector3D generateRandom(Vector3D ini,Vector3D range);
	void createParticle();
};

