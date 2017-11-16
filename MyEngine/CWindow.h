#ifndef CWindow_H
#define CWindow_H
#include <Windows.h>
#include "CD3DRender.h"

class CWindow
{
public:
  static const char *AppWindowClass;
  static CWindow *cWindow;
  static MSG msg;
  static bool isRunning;
  unsigned long preTimeShut;
  unsigned long curTimeShut;

public:
  CWindow();
  ~CWindow();

public:
  static CWindow *create(HINSTANCE h, int posX, int posY, int width, int height, bool full);
  void initWindow(HINSTANCE h, int posX, int posY, int width, int height, bool full);
 
  void startPumpMessage();

public:
  static LRESULT CALLBACK WinProc(HWND hwnd, UINT msgID, WPARAM wp, LPARAM lp);

private:
  HWND hwnd;
  CD3DRender *render;
};

#endif