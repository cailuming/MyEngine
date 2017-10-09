#ifndef CVec4D_H
#define CVec4D_H
#include"Macro.h"
_declspec(align(16))

class CVec4D {
public;
   float x;
   float y;
   float z;
   float w;
public:
	FORCEINILINE CVec4D(float x,float y,float z,float w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
public:
	FORCEINILINE float &operator[] (unsigned int index) {
		return (&x)[index];
	};
	FORCEINILINE float operator[](unsigned int index)const {
		return (&x)[index];
	};
	FORCEINILINE CVec4D operator-() {
		return CVec4D(-x,-y,-z,-w);
	};
	FORCEINILINE CVec4D operator+(const CVec4D &v) {
		return CVec4D(x+v.x, y + v.y, z + v.z, w + v.w);
	};
	FORCEINILINE CVec4D operator+=(const CVec4D &v) {
		x += v.x; y += v.y; z += v.z; w += v.w;
		return *this;
	};

	FORCEINILINE CVec4D operator-(const CVec4D &v) {
		return CVec4D(x - v.x, y - v.y, z - v.z, w - v.w);
	};
	FORCEINILINE CVec4D operator*(const CVec4D &v) {
		return CVec4D(x*v.x, y*v.y, z*v.z, w*v.w);
	};
	FORCEINILINE CVec4D operator*(float scale) {
		return CVec4D(x*scale,y*scale,z*scale,w*scale);
	};
	FORCEINILINE CVec4D operator*=(float scale) {
		x *= scale;y *= scale; z *= scale;w *= scale;
		return *this;
	};
public:
	float getLength3D() {
		return 0;
	};
	float getLength4D();
	float getSquaredLength3D();
	float getSquaredLength4D();





};
#endif