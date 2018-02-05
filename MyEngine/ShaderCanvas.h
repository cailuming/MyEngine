#pragma once
#include"Macro.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "CConstBuffer.h"
#include "CShaders.h"
#include "CFileReader.h"

class ShaderCanvas
{
private:
	ShaderCanvas();
	~ShaderCanvas();
public:
	static ShaderCanvas *canvas;
	static ShaderCanvas *create();
	static void destroy();
public:
	CVertexBuffer vBuffer;
	CIndexBuffer iBuffer;
	CConstBuffer cBuffer;
	GBuffer gbuffer;
	CShaders *shader;

public:
	void initCanvas();
	void onCompileShader(const char *shadercode);
	void updateGBuffer(D3DXMATRIX mat, float iTime, float width, float height);
	void render();
};

