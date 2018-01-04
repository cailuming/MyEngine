#include "CCamera.h"

CCamera::CCamera()
{
}


CCamera::~CCamera()
{
}

CCamera *CCamera::cam=0;
CCamera *CCamera::create() {
	if (!cam) {
		cam = new CCamera();
	}
	return cam;
};
void CCamera::destroy() {
	if (cam) {
		delete cam;
		cam = 0;
	}
};

void CCamera::rotateX(float arc) {

};

void CCamera::rotateY(float arc) {

};

void CCamera::rotateZ(float arc) {

};

void CCamera::moveFront(float off) {

};

void CCamera::moveRight(float off) {

};

void CCamera::moveUp(float off) {

};

void CCamera::updateCam() {
	D3DXVec3Cross(&up, &look, &right);
	D3DXVec3Normalize(&up, &up);
	D3DXVec3Cross(&right, &up, &look);
	D3DXVec3Normalize(&right, &right);


	matCam._11 = right.x; matCam._12 = up.x; matCam._13 = look.x; matCam._14 = 0;
	matCam._21 = right.y; matCam._22 = up.y; matCam._23 = look.y; matCam._24 = 0;
	matCam._31 = right.z; matCam._32 = up.z; matCam._33 = look.z; matCam._34 = 0;
	matCam._41 = -D3DXVec3Dot(&pos,&right); 
	matCam._42 = -D3DXVec3Dot(&pos, &up); 
	matCam._43 = -D3DXVec3Dot(&pos, &look); 
	matCam._44 = 1;

	
	matOrFinal=matCam*matOrth;
	matProjFinal = matCam*matProj;
 
};


void CCamera::initCamera(int width, int height) {
	pos = D3DXVECTOR3(0,0,0);
	look = D3DXVECTOR3(0, 0, 1);
	up = D3DXVECTOR3(0, 1, 0);
	right = D3DXVECTOR3(1, 0, 0);
	
	D3DXMatrixOrthoLH(&matOrth, width, height, 1, 1000);
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, width*1.0f / height, 1, 1000);
};