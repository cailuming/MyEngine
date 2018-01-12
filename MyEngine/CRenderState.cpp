#include "CRenderState.h"

CRenderState *CRenderState::state = 0;

CRenderState::CRenderState()
{
}

CRenderState::~CRenderState()
{
	SAFERELEASE(smState);
	SAFERELEASE(bldState);
	SAFERELEASE(rsWireState);
	SAFERELEASE(rsSolidState);
}

CRenderState *CRenderState::create() {
	if (nullptr==state) {
		state = new CRenderState();
	}
	return state;
};

void CRenderState::destroy() {
	if (state) {
		delete state;
		state = 0;
	}
};
 
void CRenderState::setRenderState(D3D11_FILL_MODE mode) {
	if (mode==D3D11_FILL_SOLID) {
		pGContext->RSSetState(rsSolidState);
	}
	else {
		pGContext->RSSetState(rsWireState);
	}
};

void CRenderState::setScissorRect(RECT rect) {
	pGContext->RSSetScissorRects(1, &rect);
	
};

void CRenderState::createSamplerState() {
	/*
	  D3D11_TEXTURE_ADDRESS_MODE:
	  D3D11_TEXTURE_ADDRESS_WRAP   =       1
	  D3D11_TEXTURE_ADDRESS_MIRROR       = 2,
	  D3D11_TEXTURE_ADDRESS_CLAMP        = 3,
	  D3D11_TEXTURE_ADDRESS_BORDER       = 4,
	  D3D11_TEXTURE_ADDRESS_MIRROR_ONCE  = 5

	  D3D11_COMPARISON_FUNC:
	  D3D11_COMPARISON_NEVER          = 1,
	  D3D11_COMPARISON_LESS           = 2,
	  D3D11_COMPARISON_EQUAL          = 3,
	  D3D11_COMPARISON_LESS_EQUAL     = 4,
	  D3D11_COMPARISON_GREATER        = 5,
	  D3D11_COMPARISON_NOT_EQUAL      = 6,
	  D3D11_COMPARISON_GREATER_EQUAL  = 7,
	  D3D11_COMPARISON_ALWAYS         = 8
	*/
	D3D11_SAMPLER_DESC SamplerDesc;
	memset(&SamplerDesc, 0, sizeof(SamplerDesc));
	SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.BorderColor[0] = 1;
	SamplerDesc.BorderColor[1] = 1;
	SamplerDesc.BorderColor[2] = 1;
	SamplerDesc.BorderColor[3] = 1;
	SamplerDesc.ComparisonFunc = D3D11_COMPARISON_GREATER;
	SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
	SamplerDesc.MaxAnisotropy = 4;
	SamplerDesc.MaxLOD = 0;
	SamplerDesc.MinLOD = 0;

	HR(pGDevice->CreateSamplerState(&SamplerDesc, &smState),"Failed to create the sampler state!");
	 
};

void CRenderState::createRasterizerState() {
	/*
	D3D11_FILL_WIREFRAME = 2,
	D3D11_FILL_SOLID = 3
	*/
	D3D11_RASTERIZER_DESC rsDesc;
	memset(&rsDesc, 0, sizeof(rsDesc));
	rsDesc.AntialiasedLineEnable = false;
	rsDesc.CullMode = D3D11_CULL_BACK;
	rsDesc.DepthClipEnable = false;
	rsDesc.FillMode = D3D11_FILL_WIREFRAME;
	rsDesc.FrontCounterClockwise = true;
	rsDesc.MultisampleEnable = false;
	rsDesc.ScissorEnable = true;
	
	HR(pGDevice->CreateRasterizerState(&rsDesc, &rsWireState),"Failed to create the RSWireState!");
	rsDesc.FillMode = D3D11_FILL_SOLID;
	HR(pGDevice->CreateRasterizerState(&rsDesc, &rsSolidState),"Failed to create the RSSolidState!");

};
 

void CRenderState::createBlendState() {
	D3D11_BLEND_DESC blendDesc;
	memset(&blendDesc, 0, sizeof(blendDesc));
	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.IndependentBlendEnable = false;
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;

	HR(pGDevice->CreateBlendState(&blendDesc, &bldState),"Failed to create BlendState!");

};
