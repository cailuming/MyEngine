#ifndef Macro_H
#define Macro_H
#include<d3d11.h>
#pragma comment(lib,"d3d11.lib")

#define HR(hr,msg) {if(FAILED(hr)){ MessageBox(0,msg,0,0);return;}}
#define SAFERELEASE(hr) {if(hr){ hr->Release();}}
#define FORCEINILINE __inline
#endif