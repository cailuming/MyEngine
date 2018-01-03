#ifndef CConstBuffer_H
#define CConstBuffer_H
#include "Macro.h"
 
class CConstBuffer
{
  public:
    CConstBuffer();
    ~CConstBuffer();

  public:
    void createBuffer(void *data,UINT32 size);
    void *lock();
    void unLock();
    void updateBuffer(void *data, UINT32 size);
  private:
    ID3D11Buffer *buffer;
   
};

#endif