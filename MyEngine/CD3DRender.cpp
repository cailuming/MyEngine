#include "CD3DRender.h"

ID3D11Device *pGDevice;
ID3D11DeviceContext *pGContext;

CD3DRender *CD3DRender::instance = 0;

//构造函数
CD3DRender::CD3DRender()
{
}
//析构函数
CD3DRender::~CD3DRender()
{
}

//通过create 创建Render实例
CD3DRender *CD3DRender::create()
{
	if (!instance)
	{
		instance = new CD3DRender();
	}
	return instance;
}

//销毁Render的实例
void CD3DRender::destroy()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

//创建D3D11设备
void CD3DRender::createDevice()
{
	D3D_FEATURE_LEVEL featureLevel;

	HR(D3D11CreateDevice(0, D3D_DRIVER_TYPE_HARDWARE, 0, D3D11_CREATE_DEVICE_SINGLETHREADED, 0, 0, D3D11_SDK_VERSION, &pGDevice, &featureLevel, &pGContext), "Failed to create D3D11 device!");
}

//创建视口模块
void CD3DRender::createViewport(HWND hwnd, int width, int height, bool full)
{
	DXGI_SWAP_CHAIN_DESC desc;
	memset(&desc, 0, sizeof(desc));
	desc.BufferCount = 1;
	desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferDesc.RefreshRate.Numerator = 0;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;

	desc.OutputWindow = hwnd;
	desc.Windowed = !full;

	IDXGIDevice1 *iDevice;
	IDXGIAdapter1 *iAdapter;
	IDXGIFactory1 *iFactory;

	HR(pGDevice->QueryInterface(__uuidof(IDXGIDevice1), (void **)&iDevice), "Failed to query the IDXGIDevice1!");
	HR(iDevice->GetParent(__uuidof(IDXGIAdapter1), (void **)&iAdapter), "Failded to get the IDXGIAdapter!");
	HR(iAdapter->GetParent(__uuidof(IDXGIFactory1), (void **)&iFactory), "Failed to get the IDXGIFactory!");

	HRESULT hr = iFactory->CreateSwapChain(pGDevice, &desc, &viewPort.d3dSwapChain);

	HR(iFactory->CreateSwapChain(pGDevice, &desc, &viewPort.d3dSwapChain), "Failed to create the swapchain!");

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
	createDepthStenciBuffer(viewPort);

	pGContext->OMSetRenderTargets(1, &viewPort.renderTargetView, viewPort.depthStencilView);
	pGContext->RSSetViewports(1, &viewPort.viewPortInfo);

	setWindowSize(width, height);
}

//创建后背缓冲
void CD3DRender::createBackBuffer(IDXGISwapChain *&pChain, ID3D11Texture2D *&ptex, ID3D11RenderTargetView *&pRtView)
{
	HR(pChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void **)&ptex), "Failed to get the swapchain back buffer!");
	D3D11_RENDER_TARGET_VIEW_DESC rtView;
	rtView.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	rtView.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtView.Texture2D.MipSlice = 0;
	HR(pGDevice->CreateRenderTargetView(ptex, &rtView, &pRtView), "Failed to create the renderTargetView!");
};

//创建深度模板缓冲
void CD3DRender::createDepthStenciBuffer(CViewPort &viewPort)
{
	ID3D11Texture2D *depthStencil;
	D3D11_TEXTURE2D_DESC tdesc;
	tdesc.Width = viewPort.viewPortInfo.Width;
	tdesc.Height = viewPort.viewPortInfo.Height;
	tdesc.MipLevels = 1;
	tdesc.ArraySize = 1;
	tdesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	tdesc.SampleDesc.Count = 1;
	tdesc.SampleDesc.Quality = 0;
	tdesc.Usage = D3D11_USAGE_DEFAULT;
	tdesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	tdesc.CPUAccessFlags = 0;
	tdesc.MiscFlags = 0;

	HR(pGDevice->CreateTexture2D(&tdesc, 0, &depthStencil), "Failed to create the depth stencil buffer!");

	D3D11_DEPTH_STENCIL_VIEW_DESC sdesc;

	sdesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	sdesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	sdesc.Texture2D.MipSlice = 0;
	sdesc.Flags = 0;

	HR(pGDevice->CreateDepthStencilView(depthStencil, &sdesc, &viewPort.depthStencilView), "Failed to create the depthStencilView!");
};

//重新设置窗口尺寸
void CD3DRender::resizeWindow(HWND hwnd, int newSizeW, int newSizeH, bool isFull)
{
	if (newSizeW != viewPort.viewPortInfo.Width || newSizeH != viewPort.viewPortInfo.Height)
	{
		pGContext->OMSetRenderTargets(0, 0, 0);
		SAFERELEASE(viewPort.backBufferTexture);
		SAFERELEASE(viewPort.renderTargetView);
		SAFERELEASE(viewPort.depthStencilView);

		viewPort.viewPortInfo.Width = newSizeW;
		viewPort.viewPortInfo.Height = newSizeH;
		viewPort.isFullScreen = isFull;
		//viewPort
		DXGI_SWAP_CHAIN_DESC desc;
		viewPort.d3dSwapChain->GetDesc(&desc);
		//viewPort.d3dSwapChain->ResizeBuffers();
	}
};

void CD3DRender::setWindowSize(int screenWidth, int screenHeight) {
	this->screenHeight = screenHeight;
	this->screenWidth = screenWidth;
}
 