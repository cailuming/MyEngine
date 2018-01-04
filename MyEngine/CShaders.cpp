#include "CShaders.h"

CShaders::CShaders()
{
	memset(this, 0, sizeof(*this));
}


CShaders::~CShaders()
{
}

void CShaders::createPixelShaderFromCompiled(const char *filename) {
	//linkage can be null
	//shaderBytesCode must be compiled
	char codeBytes[64];
	pGDevice->CreatePixelShader(codeBytes, 64, 0, &pPixelShader);
};

void CShaders::createVertexShaderFromCompiled(const char *filename) {
	char codeBytes[64];
	pGDevice->CreateVertexShader(codeBytes, 64, 0, &pVertexShader);
};
 
void CShaders::createPixelShaderFromFile(const char *shaderCode,const char *entry) {
	 
	D3DCompile(shaderCode,strlen(shaderCode),"pixel_shader",0,0,entry,"ps_5_0", 0,0, &pPShaderData,&pError);
	if (pError) {
		::OutputDebugString((char*)pError->GetBufferPointer());
	}
	HR(pGDevice->CreatePixelShader(pPShaderData->GetBufferPointer(), pPShaderData->GetBufferSize(), 0, &pPixelShader),"Failed to create pixel shader!");
	HR(D3DReflect(pPShaderData->GetBufferPointer(), pPShaderData->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&pPReflect),"Failed to create the reflection!");
	D3D11_SHADER_DESC sdesc;
	HR(pPReflect->GetDesc(&sdesc),"Failed to get the shader desc!");
};

void CShaders::createVertexShaderFromFile(const char *shaderCode, const char *entry) {
	 
	D3DCompile(shaderCode, strlen(shaderCode), "vertex_shader", 0, 0, entry, "vs_5_0", 0, 0, &pVShaderData, &pError);
	if (pError) {
		::OutputDebugString((char*)pError->GetBufferPointer());
	}
	HR(pGDevice->CreateVertexShader(pVShaderData->GetBufferPointer(), pVShaderData->GetBufferSize(), 0, &pVertexShader), "Failed to create vertex shader!");
	HR(D3DReflect(pVShaderData->GetBufferPointer(), pVShaderData->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&pVReflect), "Failed to create the reflection!");
	
	D3D11_INPUT_ELEMENT_DESC desc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	HRESULT hr = pGDevice->CreateInputLayout(desc, ARRAYSIZE(desc),pVShaderData->GetBufferPointer(),pVShaderData->GetBufferSize(), &pLayer);
	HR(hr, "Failed to create Layerout!");


};

void CShaders::clearAllShader() {
 
	SAFERELEASE(pPShaderData);
	SAFERELEASE(pVShaderData);
	SAFERELEASE(pError);
	SAFERELEASE(pVertexShader);
	SAFERELEASE(pPixelShader);
	SAFERELEASE(pPReflect);
	SAFERELEASE(pVReflect);
	SAFERELEASE(pLayer);
};