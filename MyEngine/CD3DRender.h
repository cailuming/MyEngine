#ifndef CD3DRender_H
#define CD3DRender_H
#include"Macro.h"
#include"CMatrix.h"
struct CViewPort {
	bool isFullScreen;
	CMatrix projectionMatrix;
	D3D11_VIEWPORT viewPortInfo;
	IDXGISwapChain *d3dSwapChain;
	//used for read the back buffer pixel
	ID3D11Texture2D *backBufferTexture;
	ID3D11RenderTargetView *renderTargetView;
	ID3D11DepthStencilView *depthStencilView;
	CViewPort() :isFullScreen(false) {
	
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
	ID3D11Device *pDevice;
	ID3D11DeviceContext *pContext;
 
public:
	void createDevice();
	void createViewport(HWND hwnd,int width,int height,bool full);
	void createBackBuffer(IDXGISwapChain *&pChain,ID3D11Texture2D *&ptex,ID3D11RenderTargetView *&pRtView);
	void createDepthStenciBuffer(CViewPort &viewPort);
};

#endif
