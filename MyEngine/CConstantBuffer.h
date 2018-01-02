#ifndef CConstantBuffer_H
#define CConstantBuffer_H
#include "Macro.h"
 
class CConstantBuffer
{
  public:
    CConstantBuffer();
    ~CConstantBuffer();

  public:
    void createBuffer(void *data,UINT32 size);
    void *lock();
    void unLock();
    void updateBuffer(void *data, UINT32 size);
  private:
    ID3D11Buffer *buffer;
   
};

#endif