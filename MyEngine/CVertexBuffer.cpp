#include "CVertexBuffer.h"

CVertexBuffer::CVertexBuffer()
{
	memset(this, 0, sizeof(*this));
}


CVertexBuffer::~CVertexBuffer()
{
}

void CVertexBuffer::createBuffer(UINT32 size, D3D11_USAGE usage, void *data) {
	D3D11_BUFFER_DESC BufferDesc;
	D3D11_SUBRESOURCE_DATA resource;
	memset(&BufferDesc, 0, sizeof(BufferDesc));
	memset(&resource, 0, sizeof(resource));
	BufferDesc.Usage = usage;
	BufferDesc.ByteWidth = size;
	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDesc.CPUAccessFlags = usage&D3D11_USAGE_DYNAMIC?D3D11_CPU_ACCESS_WRITE:0;
	BufferDesc.MiscFlags = 0;
	
	if (nullptr!=data) {
		resource.pSysMem = data;
	}
	
	HR(pGDevice->CreateBuffer(&BufferDesc, &resource, &buffer), "Failed to create vertex buffer!");
}

void CVertexBuffer::destroyBuffer() {
	SAFERELEASE(buffer);
}

void *CVertexBuffer::lock(int lockIndex) {
	D3D11_MAPPED_SUBRESOURCE resource;
	pGContext->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	void *pAddr = resource.pData;
	return pAddr;
}
void CVertexBuffer::unLock() {
	pGContext->Unmap(buffer, 0);
}
 
 