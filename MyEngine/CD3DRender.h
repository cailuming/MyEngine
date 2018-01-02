#ifndef CD3DRender_H
#define CD3DRender_H
#include"Macro.h"
#include"CMatrix.h"
#include"CTimer.h"
struct CViewPort {
	bool isFullScreen;
	float bgcolor[4];
	CMatrix projectionMatrix;
	D3D11_VIEWPORT viewPortInfo;
	IDXGISwapChain *d3dSwapChain;
	//used for read the back buffer pixel
	ID3D11Texture2D *backBufferTexture;
	ID3D11RenderTargetView *renderTargetView;
	ID3D11DepthStencilView *depthStencilView;
	CViewPort() :isFullScreen(false) {
		bgcolor[0] = 0;
		bgcolor[1] = 1;
		bgcolor[2] = 1;
		bgcolor[3] = 1;
	};

	~CViewPort() {
		SAFERELEASE(d3dSwapChain);
		SAFERELEASE(backBufferTexture);
		SAFERELEASE(renderTargetView);
		SAFERELEASE(depthStencilView);
	}
};

class CD3DRender {
private:
	CD3DRender();
	~CD3DRender();
public:
	static CD3DRender *instance;
	static CD3DRender *create();
	static void destroy();
public:
	CViewPort viewPort;

public:
	void createDevice();
	void createViewport(HWND hwnd,int width,int height,bool full);
	void createBackBuffer(IDXGISwapChain *&pChain,ID3D11Texture2D *&ptex,ID3D11RenderTargetView *&pRtView);
	void createDepthStenciBuffer(CViewPort &viewPort);
public:
	void resizeWindow(HWND hwnd, int newSizeW, int newSizeH, bool isFull);
 
};

#endif
