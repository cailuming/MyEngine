#ifndef CConstantBuffer_H
#define CConstantBuffer_H
#include "Macro.h"
 
class CConstantBuffer
{
  public:
    CConstantBuffer();
    ~CConstantBuffer();

  public:
    void createBuffer(void *bufferData);
    void *lock();
    void unLock();
    void updateBuffer();
  private:
    ID3D11Buffer *buffer;
   
};

#endif