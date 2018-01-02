#include "CIndexBuffer.h"

CIndexBuffer::CIndexBuffer()
{
}

CIndexBuffer::~CIndexBuffer()
{
}

void CIndexBuffer::createBuffer(int sizeBytes)
{
    D3D11_BUFFER_DESC BufferDesc;
    BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    BufferDesc.ByteWidth = sizeBytes;
    BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    BufferDesc.MiscFlags = 0;

    HR(pGDevice->CreateBuffer(&BufferDesc, 0, &buffer), "Failed to create index buffer!");
};

void CIndexBuffer::destroyBuffer()
{
    SAFERELEASE(buffer);
};

void *CIndexBuffer::lock(int lockIndex)
{
    D3D11_MAPPED_SUBRESOURCE resource;
	pGContext->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
    void *Data = resource.pData;

    int Offset = lockIndex * sizeof(int);
    return (void *)((unsigned char *)Data + Offset);
};

void CIndexBuffer::unLock()
{
	pGContext->Unmap(buffer, 0);
};

ID3D11Buffer *CIndexBuffer::getResource()
{
    return buffer;
};

int CIndexBuffer::getMaxnumIndices() {
	return maxIndicesNum;
}
