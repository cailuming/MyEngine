#ifndef D3DRender_H
#define D3DRender_H
#include"Macro.h"

struct ViewPort {
	bool isFullScreen;


};

class D3DRender {
private:
	D3DRender();
	~D3DRender();
public:
	static D3DRender *instance;
	static D3DRender *create();
	static void destroy();
public:
	ID3D11Device *pDevice;
	ID3D11DeviceContext *pContext;
	IDXGISwapChain *pChain;
public:
	void createDevice();
	void createViewport(HWND hwnd,int width,int height,bool full);
};

#endif
