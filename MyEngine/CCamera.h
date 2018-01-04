#pragma once
#include"Macro.h"
class CCamera
{
private:
	CCamera();
	~CCamera();
public:
	static CCamera *cam;
	static CCamera *create();
	static void destroy();
public:
	void rotateX(float arc);
	void rotateY(float arc);
	void rotateZ(float arc);
	void moveFront(float off);
	void moveRight(float off);
	void moveUp(float off);
	void updateCam();
public:
	D3DXVECTOR3 pos;
	D3DXVECTOR3 look;
	D3DXVECTOR3 up;
	D3DXVECTOR3 right;
	D3DXMATRIX matOrFinal;
	D3DXMATRIX matProjFinal;
	D3DXMATRIX matOrth;
	D3DXMATRIX matProj;
	D3DXMATRIX matCam;
public:
	void initCamera(int width,int height);
};

