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
	Vector3D posPart = aux->getPos();
	//comprobamos si hace efecto
	if(posPart.norm()<=mRadio)
	{
	//calculamos sol
		sol.x = -(posPart.z - mPos.z);
		sol.y =50 -(posPart.y - mPos.y);
		sol.z = (posPart.x - mPos.x);
	}
	
	
	sol = sol * fuerza;
	return sol;
}
