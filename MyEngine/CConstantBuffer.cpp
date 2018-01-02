#include "CConstantBuffer.h"

CConstantBuffer::CConstantBuffer()
{
	memset(this, 0, sizeof(*this));
}

CConstantBuffer::~CConstantBuffer()
{
}

void CConstantBuffer::createBuffer(void *data, UINT32 size)
{
    D3D11_BUFFER_DESC Desc;
    Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    Desc.Usage = D3D11_USAGE_DYNAMIC;
    Desc.ByteWidth = size;
    Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    Desc.MiscFlags = 0;
    Desc.StructureByteStride = 0;

    HRESULT Hr = pGDevice->CreateBuffer(&Desc, NULL, &buffer);
}

void *CConstantBuffer::lock()
{
    D3D11_MAPPED_SUBRESOURCE Resource;
    pGContext->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &Resource);
    return Resource.pData;
}

void CConstantBuffer::unLock()
{
	pGContext->Unmap(buffer, 0);
}

void CConstantBuffer::updateBuffer(void *data,UINT32 size)
{
    void *Data = lock();
    memcpy(Data, data, size);
    unLock();
}