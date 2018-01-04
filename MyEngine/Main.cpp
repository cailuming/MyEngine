#include "Main.h"

CWindow *window = 0;
CTimer *timer = 0;
CD3DRender *render = 0;
CShaders *shader = new CShaders();
CFileReader *reader = CFileReader::create();
CVertexBuffer vBuffer;
CIndexBuffer iBuffer;
CConstBuffer cBuffer;
CCamera *camera=CCamera::create();
ID3D11InputLayout *pLayer=0;

struct vertex {
	float px, py, pz;
	float nx, ny, nz;
	float ux, uy;
};

// constant buffer must be 16 bytes aligned
struct gBuffer {
	D3DXMATRIX mat;
	float iTime;
	float iTime1;
	float width;
	float height;
} gbuffer;

void onInit(HWND hwnd, int width, int height, bool full) {
	render = CD3DRender::create();
	render->createDevice();
	render->createViewport(hwnd, width, height, full);

	timer = CTimer::create();

	camera->initCamera(width, height);

	shader->createVertexShaderFromFile(reader->readFile("shaders/vs.hlsl"), "main");
	shader->createPixelShaderFromFile(reader->readFile("shaders/ps.hlsl"), "main");
	float size = 1;
	vertex v[] = { { -size, -size, 0, 0, 0, 1, 0, 0}, { -size,size, 0, 0, 0, 1, 0, 1 }, { size, size, 0, 0, 0, 1, 1, 1 }, { size, -size, 0, 0, 1, 1, 1, 0 } };
	WORD indexs[] = {0,1,2,0,2,3};
	vBuffer.createBuffer(sizeof(v), D3D11_USAGE_DEFAULT, v);
	iBuffer.createBuffer(6*sizeof(WORD), D3D11_USAGE_DEFAULT, indexs);
	cBuffer.createBuffer(&gbuffer, sizeof(gbuffer));
	D3D11_INPUT_ELEMENT_DESC desc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
 
	HRESULT hr = pGDevice->CreateInputLayout(desc, ARRAYSIZE(desc), shader->pVShaderData->GetBufferPointer(), shader->pVShaderData->GetBufferSize(), &pLayer);
	HR(hr,"Failed to create Layerout!");

}

void renderFunc(int delta) {
	 pGContext->ClearDepthStencilView(render->viewPort.depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
 
	 pGContext->ClearRenderTargetView(render->viewPort.renderTargetView, render->viewPort.bgcolor);
	
	 gbuffer.iTime = timer->getTickCount()*1.0f;
	 gbuffer.mat = camera->matOrFinal;
	 gbuffer.width = render->screenWidth;
	 gbuffer.height = render->screenHeight;
	
	 cBuffer.updateBuffer(&gbuffer, sizeof(gbuffer));
	 UINT stride = sizeof(vertex);
	 UINT offset = 0;
	 pGContext->IASetInputLayout(pLayer);
	 pGContext->IASetVertexBuffers(0,1,&vBuffer.buffer,&stride, &offset);
	 pGContext->IASetIndexBuffer(iBuffer.getResource(), DXGI_FORMAT_R16_UINT, 0);

	 pGContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	 pGContext->VSSetShader(shader->pVertexShader, 0, 0);
	 pGContext->PSSetShader(shader->pPixelShader, 0, 0);
	 pGContext->VSSetConstantBuffers(0, 1, &cBuffer.buffer);
	 pGContext->PSSetConstantBuffers(0, 1, &cBuffer.buffer);
	 pGContext->DrawIndexed(6, 0, 0);
	//pGContext->DrawIndexedInstanced(3, 0, 0,0,0);
	// pGContext->Draw(6,0);
	//pGContext->DrawInstanced(3, 0,0,0);
	// cBuffer.updateBuffer(&camera->matOrFinal, sizeof(D3DXMATRIX));

	 render->viewPort.d3dSwapChain->Present(0, 0);
	 camera->updateCam();
}

int _stdcall WinMain(HINSTANCE h, HINSTANCE pre, char *args, int style)
{
	window = CWindow::create(h, 0, 0, 800, 600, false);
    
	onInit(window->getWindowHwnd(),800,600,false);
	window->startPumpMessage(renderFunc);
}

