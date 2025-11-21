#pragma once
#include <iostream>
#include <cmath>

class Vector3D {
public:
    double x, y, z;

    // Constructor vacío
    Vector3D() : x(0.0), y(0.0), z(0.0) {}

    // Constructor con 3 valores
    Vector3D(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}
    ~Vector3D() {}
    // --- Operaciones aritméticas ---
    // Suma de vectores
    Vector3D operator+(const Vector3D& v) const {
        return Vector3D(x + v.x, y + v.y, z + v.z);
    }

    // Resta de vectores
    Vector3D operator-(const Vector3D& v) const {
        return Vector3D(x - v.x, y - v.y, z - v.z);
    }

    
    Vector3D operator*(double d) const {
        return Vector3D(x * d, y * d, z * d);
    }

    
    Vector3D operator/(double d) const {
        return Vector3D(x / d, y / d, z / d);
    }

    
    double Pescalar(const Vector3D& v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    
    Vector3D Pvectorial(const Vector3D& v) const {
        return Vector3D(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x
        );
    }

    // Norma (longitud del vector)
    double norm() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    // Normalización
    Vector3D normalized() const {
        double n = norm();
        if (n == 0) return Vector3D(0, 0, 0);
        return (*this) / n;
    }

    // Operador +=
    Vector3D& operator+=(const Vector3D& v) {
        x += v.x; y += v.y; z += v.z;
        return *this;
    }

    // Operador -=
    Vector3D& operator-=(const Vector3D& v) {
        x -= v.x; y -= v.y; z -= v.z;
        return *this;
    }
    // Comparación de igualdad
    bool operator==(const Vector3D& v) const {
        return x == v.x && y == v.y && z == v.z;
    }

    // Comparación de desigualdad
    bool operator!=(const Vector3D& v) const {
        return !(*this == v);
    }


};

