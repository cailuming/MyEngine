#include "CConstantBuffer.h"

CConstantBuffer::CConstantBuffer()
{
}

CConstantBuffer::~CConstantBuffer()
{
}

void CConstantBuffer::createBuffer(void *bufferData)
{
    D3D11_BUFFER_DESC Desc;
    Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    Desc.Usage = D3D11_USAGE_DYNAMIC;
    Desc.ByteWidth = sizeof(*bufferData);
    Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    Desc.MiscFlags = 0;
    Desc.StructureByteStride = 0;

    HRESULT Hr = GD3DDevice->CreateBuffer(&Desc, NULL, buffer);
}

void *CConstantBuffer::lock()
{
    D3D11_MAPPED_SUBRESOURCE Resource;
    pGDeviceContext->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &Resource);
    return Resource.pData;
}

void CConstantBuffer::unLock()
{
    pGDeviceContext->Unmap(buffer, 0);
}

void CConstantBuffer::updateBuffer(void *data)
{
    void *Data = Lock();
    memcpy(Data, data, sizeof(*data));
    Unlock();
}