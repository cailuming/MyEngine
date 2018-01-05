#pragma once
#include"Macro.h"

class CShaders
{
public:
	CShaders();
	~CShaders();
public:
	ID3D10Blob *pPShaderData;
	ID3D10Blob *pVShaderData;
	ID3D10Blob *pError;
public:
	ID3D11VertexShader *pVertexShader;
	ID3D11PixelShader *pPixelShader;
	ID3D11ShaderReflection *pPReflect;
	ID3D11ShaderReflection *pVReflect;
	ID3D11InputLayout *pLayer;
public:
	void createPixelShaderFromCompiled(const char *filename);
	void createVertexShaderFromCompiled(const char *filename);
	void createPixelShaderFromFile(const char *shaderCode, const char *entry);
	void createVertexShaderFromFile(const char *shaderCode, const char *entry);
	void createInternalVertexShader();
	void clearAllShader();
  	
public:
	const char *vsHeader;
	const char *psHeader;
	char *cmpBuff;
	void initHeaders();
	void appendVsHeaders(const char *code);
	void appendPsHeaders(const char *code);
};

