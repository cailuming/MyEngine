#include "ShaderCanvas.h"

ShaderCanvas::ShaderCanvas()
{
	memset(this, 0, sizeof(*this));
	
}


ShaderCanvas::~ShaderCanvas()
{
}

ShaderCanvas *ShaderCanvas::canvas=0;

ShaderCanvas *ShaderCanvas::create() {
	if (nullptr==canvas) {
		canvas = new ShaderCanvas();
	}
	return canvas;
};

void ShaderCanvas::destroy() {
	if (canvas) {
		delete canvas;
		canvas = 0;
	}
};

void ShaderCanvas::initCanvas() {
	float size = 1;
	vertex v[] = { { -size, -size, 0.9, 0, 0, 1, 0, 0 },{ -size,size, 0.9, 0, 0, 1, 0, 1 },{ size, size, 0.9, 0, 0, 1, 1, 1 },{ size, -size, 0.9, 0, 1, 1, 1, 0 } };
	WORD indexs[] = { 0,1,2,0,2,3 };
	vBuffer.createBuffer(sizeof(v), D3D11_USAGE_DEFAULT, v);
	iBuffer.createBuffer(6 * sizeof(WORD), D3D11_USAGE_DEFAULT, indexs);
	cBuffer.createBuffer(&gbuffer, sizeof(gbuffer));
	shader = new CShaders();
};

void ShaderCanvas::onCompileShader(const char *shadercode) {
	
	shader->createInternalVertexShader();
	shader->createPixelShaderFromFile(shadercode, "main");
}

void ShaderCanvas::updateGBuffer(D3DXMATRIX mat, float iTime,float width,float height) {
	gbuffer.iTime = iTime;
	gbuffer.mat = mat;
	gbuffer.width = width;
	gbuffer.height = height;

	cBuffer.updateBuffer(&gbuffer, sizeof(gbuffer));
}

void ShaderCanvas::render() {
	UINT stride = sizeof(vertex);
	UINT offset = 0;
	pGContext->IASetInputLayout(shader->pLayer);
	pGContext->IASetVertexBuffers(0, 1, &vBuffer.buffer, &stride, &offset);
	pGContext->IASetIndexBuffer(iBuffer.getResource(), DXGI_FORMAT_R16_UINT, 0);

	pGContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	pGContext->VSSetShader(shader->pVertexShader, 0, 0);
	pGContext->PSSetShader(shader->pPixelShader, 0, 0);
	pGContext->VSSetConstantBuffers(0, 1, &cBuffer.buffer);
	pGContext->PSSetConstantBuffers(0, 1, &cBuffer.buffer);
	pGContext->DrawIndexed(6, 0, 0);
};
