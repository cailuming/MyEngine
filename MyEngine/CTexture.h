#pragma once
#include"Macro.h"
class CTexture
{
public:
	CTexture();
	~CTexture();
public:
	ID3D11Texture2D *pTex2D;
	ID3D11Texture3D *pTex3D;
	ID3D11ShaderResourceView *tex;
public:
	void createShaderTexture2D(int width,int height,unsigned char *data);
	void createStageTexture2D();

};

