#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
class Sphere;
using namespace physx;

class Vector3D: public RenderItem
{
public:
	Vector3D(Vector3 v);
	
	~Vector3D();
	float getX() {
		return x;
	};
	float getY() { return y; }
	float getZ() { return z; }
	void operator=(Vector3D other)
	{
		x = other.getX();
		y = other.getY();
		z = other.getZ();
	};
	void operator +=(Vector3D other)
	{
		x = x + other.getX();
		y = y + other.getY();
		z = z + other.getZ();
	}
	Vector3D operator +(Vector3D other)
	{
		Vector3D aux({0,0,0});
		aux.x = x - other.getX();
		aux.y = y - other.getY();
		aux.z = z - other.getZ();
		return aux;
	}
	void Normalize()
	{
		Vector3 aux = { x,y,z };
		aux.normalize();
		x = aux.x;
		y = aux.y;
		z = aux.z;
	}
	int Modulo()
	{
		return sqrt(x*x+y*y+z*z);
	}
	void operator *(int n)
	{
		x = x * n;
		y = y * n;
		z = z * n;
	}int operator *(Vector3D other)
	{
		return x * other.getX() + y * other.getY() + other.getZ() * z;
	}
	void operator /(int n)
	{
		x = x / n;
		y = y / n;
		z = z / n;
	}
	bool operator==(Vector3D other)
	{
		return ((getX() == other.getX()) && (getY() == other.getY()) && (getZ() == other.getZ()));
	}
	bool operator!=(Vector3D other)
	{
		return !(*this == other);
	}
private:
	
	float x, y, z;
	
};

