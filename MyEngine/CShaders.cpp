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
};

void CShaders::getShaderParamLocation() {
	
};
void CShaders::setShaderParam1f() {

};
void CShaders::setShaderParam2f() {

};
void CShaders::setShaderParam3f() {

};
void CShaders::setShaderParam4f() {

};
void CShaders::setShaderParam1i() {

};
void CShaders::setShaderParam2i() {

};
void CShaders::setShaderParam3i() {

};
void CShaders::setShaderParam4i() {

};
void CShaders::setShaderParamMat() {

};
void CShaders::setShaderParamMatArray() {

};
