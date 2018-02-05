#pragma once
#include"Macro.h"
class CRenderState
{
private:
	CRenderState();
	~CRenderState();
public:
	static CRenderState *state;
	static CRenderState *create();
	static void destroy();
public:
	void setScissorRect(RECT rect);
	void setRenderState(D3D11_FILL_MODE mode);
	void initAllStates();
private:
	void createSamplerState();
	void createRasterizerState();
	void createBlendState();

private:
	ID3D11SamplerState *smState;
	ID3D11BlendState *bldState;
	ID3D11RasterizerState *rsWireState;
	ID3D11RasterizerState *rsSolidState;
	 
};

