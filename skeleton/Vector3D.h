#pragma once
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
class Sphere;
using namespace physx;

class Vector3D: public RenderItem
{
public:
	float x, y, z;
	Vector3D() { x = 0.f, y = 0.f, z = 0.f; }
	Vector3D(Vector3 v);
	
	Vector3D(float X, float Y, float Z) :x(X), y(Y), z(Z) {};
	~Vector3D();
	
	void  operator =(Vector3D other)
	{		
		x= other.x;
		y = other.y;
		z = other.z;
	};
	void operator +=(Vector3D other)
	{
		
		x = x + other.x;
		y = y + other.y;
		z = z + other.z;
	}
	Vector3D operator +(Vector3D other)
	{
		Vector3D aux({0,0,0});
		aux.x = x + other.x;
		aux.y = y + other.y;
		aux.z = z + other.z;
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
	double Modulo()
	{
		return sqrt(x*x+y*y+z*z);
	}
	Vector3D operator *(float n)
	{
		Vector3D aux({ 0,0,0 });
		aux.x = x * n;
		aux.y = y * n;
		aux.z = z * n;
		return aux;
	}int operator *(Vector3D other)
	{
		return x * other.x + y * other.y + other.z * z;
	}
	void operator /(float n)
	{
		x = x / n;
		y = y / n;
		z = z / n;
	}
	bool operator==(Vector3D other)
	{
		return ((x == other.x) && (y == other.y) && (z == other.z));
	}
	bool operator!=(Vector3D other)
	{
		return !(*this == other);
	}
private:
	
	
	
};

