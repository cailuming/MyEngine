#include "CShaders.h"

CShaders::CShaders()
{
	memset(this, 0, sizeof(*this));
	initHeaders();
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

void CShaders::createInternalVertexShader() {
	D3DCompile(vsHeader, strlen(vsHeader), "vertex_shader", 0, 0, "main", "vs_5_0", 0, 0, &pVShaderData, &pError);
	if (pError) {
		::OutputDebugString((char*)pError->GetBufferPointer());
		MessageBox(0, ((char*)pError->GetBufferPointer()), "提示", 0);
		return;
	}

	HR(pGDevice->CreateVertexShader(pVShaderData->GetBufferPointer(), pVShaderData->GetBufferSize(), 0, &pVertexShader), "Failed to create vertex shader!");
	HR(D3DReflect(pVShaderData->GetBufferPointer(), pVShaderData->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&pVReflect), "Failed to create the reflection!");

	D3D11_INPUT_ELEMENT_DESC desc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	HRESULT hr = pGDevice->CreateInputLayout(desc, ARRAYSIZE(desc), pVShaderData->GetBufferPointer(), pVShaderData->GetBufferSize(), &pLayer);
	HR(hr, "Failed to create Layerout!");

};
 
void CShaders::createPixelShaderFromFile(const char *shaderCode,const char *entry) {
	appendPsHeaders(shaderCode);
	D3DCompile(cmpBuff,strlen(cmpBuff),"pixel_shader",0,0,entry,"ps_5_0", 0,0, &pPShaderData,&pError);
	if (pError) {
		::OutputDebugString((char*)pError->GetBufferPointer());
		MessageBox(0,((char*)pError->GetBufferPointer()),"提示",0);
		return;
	}
	HR(pGDevice->CreatePixelShader(pPShaderData->GetBufferPointer(), pPShaderData->GetBufferSize(), 0, &pPixelShader),"Failed to create pixel shader!");
	HR(D3DReflect(pPShaderData->GetBufferPointer(), pPShaderData->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&pPReflect),"Failed to create the reflection!");
	D3D11_SHADER_DESC sdesc;
	HR(pPReflect->GetDesc(&sdesc),"Failed to get the shader desc!");
	
	delete cmpBuff;
};

void CShaders::createVertexShaderFromFile(const char *shaderCode, const char *entry) {
	appendVsHeaders(shaderCode);
	D3DCompile(cmpBuff, strlen(cmpBuff), "vertex_shader", 0, 0, entry, "vs_5_0", 0, 0, &pVShaderData, &pError);
	if (pError) {
		::OutputDebugString((char*)pError->GetBufferPointer());
		MessageBox(0, ((char*)pError->GetBufferPointer()), "提示", 0);
		return;
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

	delete cmpBuff;
};

void CShaders::initHeaders() {
	vsHeader =
	"cbuffer gBuffer : register(b0)\
	{                            \
	    matrix mat;              \
	    float iTime;             \
	    float iTime1;            \
	    float2 iResolution;      \
	};                           \
	struct VertexShaderInput     \
	{                            \
		float3 pos : POSITION;   \
		float3 norm : NORMAL;    \
		float2 tex : TEXCOORD;   \
                                 \
	};                           \
                                 \
	struct VertexShaderOut       \
	{                            \
		float4 pos : SV_POSITION;\
		float3 norm : NORMAL;    \
		float2 tex : TEXCOORD;   \
                                 \
	};                           \
                                 \
	VertexShaderOut main(VertexShaderInput input)\
	{                                            \
		VertexShaderOut outp;                    \
		float4 pos = float4(input.pos, 1.0f);    \
		                \
		outp.pos = pos;                          \
		outp.norm = input.norm;                  \
		outp.tex = input.tex;                    \
		return outp;                             \
	}\
	";
	psHeader =
		"cbuffer gBuffer : register(b0) \
	    {\
		    matrix mat;\
		    float iTime;\
		    float iTime1;\
		    float2 iResolution;\
	    };\
                               \
                               \
    	struct PixelShaderInput\
	    {\
		    float4 pos : SV_POSITION;\
		    float3 norm : NORMAL;\
		    float2 tex : TEXCOORD;\
	    }; ";

	
};
 
void CShaders::appendVsHeaders(const char *code) {
	int codelen = strlen(code) + strlen(vsHeader);
	cmpBuff = new char[codelen + 1];
	memset(cmpBuff, 0, sizeof(cmpBuff));
	sprintf_s(cmpBuff, codelen, "%s%s", vsHeader, code);
	 
};

void CShaders::appendPsHeaders(const char *code) {
	int codelen = strlen(code) + strlen(psHeader);
	cmpBuff = new char[codelen + 1];
	char *p = cmpBuff;

	memcpy(p, psHeader, strlen(psHeader));
	p += strlen(psHeader);
	memcpy(p, code, strlen(code));

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