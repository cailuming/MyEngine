#pragma once
#include"Macro.h"

class CVertexBuffer
{
public:
	CVertexBuffer();
	~CVertexBuffer();
public:
	void createBuffer(UINT32 size,D3D11_USAGE usage,void *data);
	void destroyBuffer();
	void *lock(int lockIndex);
	void unLock();
public:
	ID3D11Buffer *getResource();
private:
	unsigned int maxIndicesNum;
	ID3D11Buffer *buffer;
};

