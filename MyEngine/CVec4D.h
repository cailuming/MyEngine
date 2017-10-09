#ifndef CVec4D_H
#define CVec4D_H
#include"Macro.h"
_declspec(align(16))

class CVec4D {
public:
   float x;
   float y;
   float z;
   float w;
public:
	FORCEINLINE CVec4D(float x,float y,float z,float w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
public:
	FORCEINLINE float &operator[] (unsigned int index) {
		return (&x)[index];
	};
	FORCEINLINE float operator[](unsigned int index)const {
		return (&x)[index];
	};
	FORCEINLINE CVec4D operator-() {
		return CVec4D(-x,-y,-z,-w);
	};
	FORCEINLINE CVec4D operator+(const CVec4D &v) {
		return CVec4D(x+v.x, y + v.y, z + v.z, w + v.w);
	};
	FORCEINLINE CVec4D operator+=(const CVec4D &v) {
		x += v.x; y += v.y; z += v.z; w += v.w;
		return *this;
	};

	FORCEINLINE CVec4D operator-(const CVec4D &v) {
		return CVec4D(x - v.x, y - v.y, z - v.z, w - v.w);
	};
	FORCEINLINE CVec4D operator*(const CVec4D &v) {
		return CVec4D(x*v.x, y*v.y, z*v.z, w*v.w);
	};
	FORCEINLINE CVec4D operator*(float scale) {
		return CVec4D(x*scale,y*scale,z*scale,w*scale);
	};
	FORCEINLINE CVec4D operator*=(float scale) {
		x *= scale;y *= scale; z *= scale;w *= scale;
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
#endif