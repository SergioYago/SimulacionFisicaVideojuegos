#include "TorbellinoGenerator.h"



TorbellinoGenerator::TorbellinoGenerator(Vector3D pos, float fuerza, float radioEfecto):GeneradorFuerza({0,0,0},fuerza)
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
	if((posPart.norm()<=mRadio)&&active)
	{
		//std::cout << "entra"<<std::endl;
	//calculamos sol
		sol.x = -(posPart.z);
		sol.y =50 -(posPart.y);
		sol.z = (posPart.x);
		
	}
	sol = sol * fuerza;
	return sol;
}
