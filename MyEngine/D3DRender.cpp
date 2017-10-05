#include"D3DRender.h"

D3DRender *D3DRender::instance = 0;

D3DRender::D3DRender() {

}

D3DRender::~D3DRender() {

}

D3DRender *D3DRender::create() {

}

void D3DRender::destroy() {

}

void D3DRender::createDevice() {
   D3D_FEATURE_LEVEL featureLevel;
   
   HR(D3D11CreateDevice(0, D3D_DRIVER_TYPE_HARDWARE, 0, D3D11_CREATE_DEVICE_SINGLETHREADED, 0, 0, D3D11_SDK_VERSION, &pDevice, &featureLevel, &pContext),"Failed to create D3D11 device!");

}

void D3DRender::createViewport(HWND hwnd, int width, int height, bool full) {
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

	HR(pDevice->QueryInterface(__uuidof(IDXGIDevice1), (void**)&iDevice),"Failed to query the IDXGIDevice1!");
	HR(iDevice->GetParent(__uuidof(IDXGIAdapter1), (void**)&iAdapter),"Failded to get the IDXGIAdapter!");
	HR(iAdapter->GetParent(__uuidof(IDXGIFactory1),(void**)&iFactory),"Failed to get the IDXGIFactory!");
    
	HR(iFactory->CreateSwapChain(pDevice, &desc, &pChain),"Failed to create the swapchain!");

	SAFERELEASE(iDevice);
	SAFERELEASE(iAdapter);
	SAFERELEASE(iFactory);
}