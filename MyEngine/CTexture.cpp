#include "CTexture.h"

CTexture::CTexture()
{
	memset(this, 0, sizeof(*this));
}


CTexture::~CTexture()
{
}

void CTexture::createShaderTexture2D(int width, int height, unsigned char *data) {
	D3D11_TEXTURE2D_DESC tdesc;
	D3D11_SUBRESOURCE_DATA sdata;
	memset(&tdesc, 0, sizeof(tdesc));
	memset(&sdata, 0, sizeof(sdata));

	tdesc.ArraySize = 1;
	tdesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	tdesc.CPUAccessFlags = 0;
	tdesc.Format = DXGI_FORMAT_A8_UNORM;
	tdesc.Width = width;
	tdesc.Height = height;
	tdesc.MipLevels = 1;
	tdesc.MiscFlags = 0;
	tdesc.SampleDesc.Count = 1;
	tdesc.SampleDesc.Quality = 0;
	tdesc.Usage = D3D11_USAGE_DEFAULT;
	
	
	float *sd = new  float[width*height];
	for (int i = 0; i < height;i++) {
		for (int j = 0; j < width;j++) {
			sd[i*width + j] = data[i*width + j];
		}
	}
	sdata.pSysMem = data;
	sdata.SysMemPitch = width;
	sdata.SysMemSlicePitch = width*height;

	HR(pGDevice->CreateTexture2D(&tdesc, &sdata,&pTex2D),"Failed to create texture2D!");
	 
	HR(pGDevice->CreateShaderResourceView(pTex2D, 0, &tex),"Failed to create shaderResource!");
	delete[] sd;
};

void CTexture::createStageTexture2D() {

};
