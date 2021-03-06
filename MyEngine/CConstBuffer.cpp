#include "CConstBuffer.h"

CConstBuffer::CConstBuffer()
{
	memset(this, 0, sizeof(*this));
}

CConstBuffer::~CConstBuffer()
{
	SAFERELEASE(buffer);
}

void CConstBuffer::createBuffer(void *data, UINT32 size)
{
    D3D11_BUFFER_DESC Desc;
    Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    Desc.Usage = D3D11_USAGE_DYNAMIC;
    Desc.ByteWidth = size;
    Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    Desc.MiscFlags = 0;
    Desc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA resource;
	memset(&resource, 0, sizeof(resource));
	resource.pSysMem = data;
    HRESULT Hr = pGDevice->CreateBuffer(&Desc, &resource, &buffer);
}

void *CConstBuffer::lock()
{
    D3D11_MAPPED_SUBRESOURCE Resource;
    pGContext->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &Resource);
    return Resource.pData;
}

void CConstBuffer::unLock()
{
	pGContext->Unmap(buffer, 0);
}

void CConstBuffer::updateBuffer(void *data,UINT32 size)
{
    void *Data = lock();
    memcpy(Data, data, size);
    unLock();
}