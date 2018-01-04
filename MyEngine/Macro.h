#ifndef Macro_H
#define Macro_H
#include<d3dx9.h>
#include <d3d11.h>
#include <D3Dcompiler.h>
#include <xnamath.h>
#include <iostream>

#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

#define HR(hr, msg)                   \
    {                                 \
        if (FAILED(hr))               \
        {                             \
            MessageBox(0, msg, 0, 0); \
            return;                   \
        }                             \
    }
#define SAFERELEASE(hr)    \
    {                      \
        if (hr)            \
        {                  \
            hr->Release(); \
        }                  \
    }

extern ID3D11Device *pGDevice;
extern ID3D11DeviceContext *pGContext;

#endif