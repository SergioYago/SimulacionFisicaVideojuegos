#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
using namespace physx;

class Sphere: public RenderItem
{
public:
	Sphere(PxReal ir=0,PxVec3 pos ={0,0,0},PxVec4 color={0,0,0,1});
	~Sphere();
	void setPos(Vector3 v) { tr.p = v; }
	
private:
	PxShape* shape;
	PxTransform tr;
	PxSphereGeometry sphere; 
	RenderItem* item;
	
};
