#include"CD3DRender.h"

CD3DRender *CD3DRender::instance = 0;

CD3DRender::CD3DRender() {

}

CD3DRender::~CD3DRender() {

}

CD3DRender *CD3DRender::create() {

}

void CD3DRender::destroy() {

}

void CD3DRender::createDevice() {
   D3D_FEATURE_LEVEL featureLevel;
   
   HR(D3D11CreateDevice(0, D3D_DRIVER_TYPE_HARDWARE, 0, D3D11_CREATE_DEVICE_SINGLETHREADED, 0, 0, D3D11_SDK_VERSION, &pDevice, &featureLevel, &pContext),"Failed to create D3D11 device!");

}

void CD3DRender::createViewport(HWND hwnd, int width, int height, bool full) {
	DXGI_SWAP_CHAIN_DESC desc;
	memset(&desc, 0, sizeof(desc));
	desc.BufferCount = 1;
	desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.RefreshRate.Denominator = 0;
	desc.BufferDesc.RefreshRate.Numerator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	desc.OutputWindow = hwnd;
	desc.Windowed = !full;

	IDXGIDevice1 *iDevice;
	IDXGIAdapter1 *iAdapter;
	IDXGIFactory1 *iFactory;
	CViewPort viewPort;

	HR(pDevice->QueryInterface(__uuidof(IDXGIDevice1), (void**)&iDevice),"Failed to query the IDXGIDevice1!");
	HR(iDevice->GetParent(__uuidof(IDXGIAdapter1), (void**)&iAdapter),"Failded to get the IDXGIAdapter!");
	HR(iAdapter->GetParent(__uuidof(IDXGIFactory1),(void**)&iFactory),"Failed to get the IDXGIFactory!");
    
	HR(iFactory->CreateSwapChain(pDevice, &desc, &viewPort.d3dSwapChain),"Failed to create the swapchain!");

	SAFERELEASE(iDevice);
	SAFERELEASE(iAdapter);
	SAFERELEASE(iFactory);

	viewPort.viewPortInfo.Width = width;
	viewPort.viewPortInfo.Height = height;
	viewPort.viewPortInfo.MaxDepth = 1;
	viewPort.viewPortInfo.MinDepth = 0;
	viewPort.viewPortInfo.TopLeftX = 0;
	viewPort.viewPortInfo.TopLeftY = 0;

	createBackBuffer(viewPort.d3dSwapChain, viewPort.backBufferTexture, viewPort.renderTargetView);
}

void CD3DRender::createBackBuffer(IDXGISwapChain *&pChain, ID3D11Texture2D *&ptex, ID3D11RenderTargetView *&pRtView) {
	HR(pChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&ptex),"Failed to get the swapchain back buffer!");
	D3D11_RENDER_TARGET_VIEW_DESC rtView;
	rtView.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	rtView.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtView.Texture2D.MipSlice = 0;
	HR(pDevice->CreateRenderTargetView(ptex, &rtView, &pRtView),"Failed to create the renderTargetView!");
};

void CD3DRender::createDepthStenciBuffer(CViewPort &viewPort) {
	ID3D11Texture2D *depthStencil;
	D3D11_TEXTURE2D_DESC tdesc;
};