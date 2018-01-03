#pragma once
#include"Macro.h"

class CShaders
{
public:
	CShaders();
	~CShaders();
private:
	ID3D10Blob *pPShaderData;
	ID3D10Blob *pVShaderData;
	ID3D10Blob *pError;
	ID3D11VertexShader *pVertexShader;
	ID3D11PixelShader *pPixelShader;
	ID3D11ShaderReflection *pPReflect;
	ID3D11ShaderReflection *pVReflect;

public:
	void createPixelShaderFromCompiled(const char *filename);
	void createVertexShaderFromCompiled(const char *filename);
	void createPixelShaderFromFile(const char *shaderCode, const char *entry);
	void createVertexShaderFromFile(const char *shaderCode, const char *entry);
	void getShaderParamLocation();
	void setShaderParam1f();
	void setShaderParam2f();
	void setShaderParam3f();
	void setShaderParam4f();
	void setShaderParam1i();
	void setShaderParam2i();
	void setShaderParam3i();
	void setShaderParam4i();
	void setShaderParamMat();
	void setShaderParamMatArray();

};

