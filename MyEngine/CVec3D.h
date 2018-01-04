#pragma once
#include"Macro.h"
_declspec(align(16))

class CVec3D
{
public:
	CVec3D();
	~CVec3D();
public:
    float x;
	float y;
	float z;
		 
public:
	FORCEINLINE CVec3D(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
public:
	FORCEINLINE float &operator[] (unsigned int index) {
		return (&x)[index];
	};
	
	FORCEINLINE float operator[](unsigned int index)const {
		return (&x)[index];
	};
	FORCEINLINE CVec3D operator-() {
		return CVec3D(-x, -y, -z);
	};
	FORCEINLINE CVec3D operator+(const CVec3D &v) {
		return CVec3D(x + v.x, y + v.y, z + v.z);
	};
	FORCEINLINE CVec3D operator+=(const CVec3D &v) {
		x += v.x; y += v.y; z += v.z;
		return *this;
	};

	FORCEINLINE CVec3D operator-(const CVec3D &v) {
		return CVec3D(x - v.x, y - v.y, z - v.z);
	};
	FORCEINLINE CVec3D operator*(const CVec3D &v) {
		return CVec3D(x*v.x, y*v.y, z*v.z);
	};
	
	FORCEINLINE CVec3D operator*(float scale) {
		return CVec3D(x*scale, y*scale, z*scale);
	};
	
	FORCEINLINE CVec3D operator*=(float scale) {
		x *= scale; y *= scale; z *= scale;
		return *this;
	};
public:
//get the vector length of 3D 
	float getLength3D() {
		return 0;
	};

//get the vector length of 4D
	float getLength4D() {

	};

//get the vector squared length of 3D
	float getSquaredLength3D() {

	};

//get the vector squared length of 4D
	float getSquaredLength4D() {

	};
};
