#pragma once
#include "Macro.h"
#include "CVec4D.h"
#include "CVertexBuffer.h"
class CQuad
{
public:
	CQuad();
	~CQuad();
public:
	CVertexBuffer buffer;
public:
	struct vertex {
		CVec4D pos;
		CVec4D norm;
		
	};
};

