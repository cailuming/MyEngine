#include "Main.h"

CWindow *window = 0;
CTimer *timer = 0;
CD3DRender *render = 0;

void onInit(HWND hwnd, int width, int height, bool full) {
	render = CD3DRender::create();
	render->createDevice();
	render->createViewport(hwnd, width, height, full);

	timer = CTimer::create();
}

void renderFunc(int delta) {
	pGContext->ClearDepthStencilView(render->viewPort.depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);

	render->viewPort.bgcolor[0] = cos(CTimer::create()->curTimeShut*0.0001)*0.7 + 0.6;
	render->viewPort.bgcolor[1] = sin(CTimer::create()->curTimeShut*0.001)*0.2 + 0.5;
	render->viewPort.bgcolor[2] = cos(CTimer::create()->curTimeShut*0.0001)*0.7 + 0.3;

	pGContext->ClearRenderTargetView(render->viewPort.renderTargetView, render->viewPort.bgcolor);
	 
	render->viewPort.d3dSwapChain->Present(0, 0);
}

int _stdcall WinMain(HINSTANCE h, HINSTANCE pre, char *args, int style)
{
	window = CWindow::create(h, 0, 0, 800, 600, false);
    
	onInit(window->getWindowHwnd(),800,600,false);
	window->startPumpMessage(renderFunc);
}

