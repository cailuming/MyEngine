#ifndef Macro_H
#define Macro_H

#include <d3d11.h>
#include <xnamath.h>
#pragma comment(lib, "d3d11.lib")

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