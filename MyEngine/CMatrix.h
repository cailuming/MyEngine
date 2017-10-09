#ifndef CMatrix_H
#define CMatrix_H
#include"Macro.h"

struct CMatrix {
public:
	__inline CMatrix() {
		memset(this, 0, sizeof(*this));
	};
	~CMatrix() {};
public:
	_declspec(align(16)) float M[4][4];
public:
	FORCEINLINE void setIdentity() {
		M[0][0] = 1.0f;
		M[1][1] = 1.0f;
		M[2][2] = 1.0f;
		M[3][3] = 1.0f;
	};

	FORCEINLINE CMatrix operator *(const CMatrix &mat) {
		CMatrix retMatrix;
		XMMATRIX mat1 = XMLoadFloat4x4A((XMFLOAT4X4A*)&mat);
		XMMATRIX mat2 = XMLoadFloat4x4A((XMFLOAT4X4A*)this);
		XMMATRIX matr = XMMatrixMultiply(mat2, mat1);
		XMStoreFloat4x4A((XMFLOAT4X4A*)&retMatrix, matr);
	};

	FORCEINLINE CMatrix operator *=(const CMatrix &mat) {
	 
		XMMATRIX mat1 = XMLoadFloat4x4A((XMFLOAT4X4A*)&mat);
		XMMATRIX mat2 = XMLoadFloat4x4A((XMFLOAT4X4A*)this);
		XMMATRIX matr = XMMatrixMultiply(mat2, mat1);
		XMStoreFloat4x4A((XMFLOAT4X4A*)this, matr);
	};
 
};
#endif