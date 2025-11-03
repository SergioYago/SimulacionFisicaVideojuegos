#include "TorbellinoGenerator.h"



TorbellinoGenerator::TorbellinoGenerator(Vector3D pos, float fuerza, float radioEfecto)
{
	mPos = pos;
	mRadio = radioEfecto;
}

TorbellinoGenerator::~TorbellinoGenerator()
{
}

Vector3D TorbellinoGenerator::getForce(Particle* aux)
{
	//la funcion era rara, y hay que multiplicar el vector3d fianl por la fuerza
	Vector3D sol = { 0,0,0 };
	Vector3D posPart = aux->getPos()-mPos;
	//comprobamos si hace efecto
	if(posPart.norm()<=mRadio)
	{
	//calculamos sol
		sol.x = -(posPart.z - mPos.z);
		sol.y =50 -(posPart.y - mPos.y);
		sol.z = (posPart.x - mPos.x);
	}

	Vector3D force = { 0,0,0 };
	if (sol.x != 0)
	{
		force.x = (sol.x * fuerza - aux->getVel().x) * k1;
	}
	if (sol.y != 0) {
		force.y = (sol.y * fuerza - aux->getVel().y) * k1;
	}
	if (sol.z != 0)
	{
		force.z = (sol.z * fuerza - aux->getVel().z) * k1;
	}
	return force;
}
