#include "Main.h"

CWindow *window = 0;
CTimer *timer =         CTimer::create();
CD3DRender *render =    CD3DRender::create(); 
ShaderCanvas *canvas =  ShaderCanvas::create();
CCamera *camera=        CCamera::create();
CFileReader *reader =   CFileReader::create();
CFontData *font = CFontData::create();
CRenderState *rState = CRenderState::create();

void onShowHelp() {
	system("start https://msdn.microsoft.com/en-us/library/windows/desktop/bb509615(v=vs.85).aspx");
}

void onResetShader() {
	reader->readConfigFile("config.ini");
	canvas->onCompileShader(reader->readShaderFile(0));
}
 
void onInit(HWND hwnd, int width, int height, bool full) {
	 
	render->createDevice();
	render->createViewport(hwnd, width, height, full);
	camera->initCamera(width, height);
	canvas->initCanvas();
	canvas->onCompileShader(reader->readShaderFile(0));
	font->initFontFromFile("Fonts/simkai.ttf");
	font->genFontTexture(reader->readDataFile("Fonts/font.txt"));
	font->onCompileShader(reader->readShaderFile("shaders/font.hlsl"));
	rState->initAllStates();
	//rState->setRenderState(D3D11_FILL_WIREFRAME);
}

void renderFunc(int delta) {
	 pGContext->ClearDepthStencilView(render->viewPort.depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
 
	 pGContext->ClearRenderTargetView(render->viewPort.renderTargetView, render->viewPort.bgcolor);
	  
	//pGContext->DrawIndexedInstanced(3, 0, 0,0,0);
	// pGContext->Draw(6,0);
	//pGContext->DrawInstanced(3, 0,0,0);
	// cBuffer.updateBuffer(&camera->matOrFinal, sizeof(D3DXMATRIX));
	 canvas->updateGBuffer(camera->matOrFinal, timer->getTickCount()*1.0f,reader->config.screenWidth,reader->config.screenHeight);
	 font->updateGBuffer(camera->matOrFinal, timer->getTickCount()*1.0f, reader->config.screenWidth, reader->config.screenHeight);
	
	 canvas->render();
	 font->render();

	 render->viewPort.d3dSwapChain->Present(0, 0);
	 camera->updateCam();
}

void callBack(UINT msgID, WPARAM wp, LPARAM lp)
{
	int menuID = 0;
	switch (msgID)
	{
	case WM_COMMAND:
		 
		menuID = LOWORD(wp);
		if (menuID==1001) {
			onResetShader();
		}
		else if (menuID == 2001) {
			onShowHelp();
		}
		break;
	 
	case WM_KEYUP:
		if (wp == VK_SPACE) {
			onResetShader();
		}
		break;
	}
};

int _stdcall WinMain(HINSTANCE h, HINSTANCE pre, char *args, int style)
{
	int sw = 1280;
	int sh = 720;

	reader->readConfigFile("config.ini");

	window = CWindow::create(h, 0, 0, reader->config.screenWidth, reader->config.screenHeight, false);
	window->setMessageCallBack(callBack);

	onInit(window->getWindowHwnd(), reader->config.screenWidth, reader->config.screenHeight,false);
	
	window->startPumpMessage(renderFunc);
}
 