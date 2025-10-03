#include "Sphere.h"



using namespace physx;
Sphere::Sphere(PxReal ir, PxVec3 pos, PxVec4 color)
{
	sphere.radius = ir;
	tr.p = pos;
	tr.q = { 0,0,0,0 };
	item = new RenderItem(CreateShape(PxSphereGeometry(ir)), &tr, color);
}



Sphere::~Sphere()
{
	DeregisterRenderItem(item);
	item = nullptr;
}
