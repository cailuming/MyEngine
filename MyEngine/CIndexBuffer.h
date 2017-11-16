#ifndef CIndexBuffer_H
#define CIndexBuffer_H
#include"Macro.h"

class CIndexBuffer
{
public:
	CIndexBuffer();
	~CIndexBuffer();
public:
	void createBuffer();
	void destroyBuffer();
	void getMaxnumIndices();
	void *lock();
	void unLock();
public:
	ID3D11Buffer *getResource();
private:
	unsigned int maxIndicesNum;
	ID3D11Buffer *buffer;
};

#endif