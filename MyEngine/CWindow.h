#ifndef CWindow_H
#define CWindow_H
#include <Windows.h>

class CWindow
{
  public:
    static const char *AppWindowClass[];

  public:
    CWindow();
    ~CWindow();

  public:
    static CWindow *create();
    HWND getHwnd() const;

    void setWindowSize(int width, int height);

    float getDPIScaleFactor() const;

    void setDPIScaleFactor();

    void onWindowMinimized();

    void onWindowRestored();

    float getAspectRatio() const;

  public:
    void reshapeWindow(int X, int Y, int width, int height);
    bool getFullScreenInfo(int &X, int &Y, int &width, int &height);

    bool isMaximized();
    bool isMinimized();
    bool isVisible();
    bool setWindowFocus();
    void setOpacity();
    void forceToFront();
    void destroyWindow();
    void minimizeWindow();
    void maxmizeWindow();
    void restoreWindow();
    void showWindow();
    void hideWindow();
    void setWindowMode();
    
    int getWindowBorderSize();
    int getWindowTitleBarSize();

  private:
    HWND hwnd;
    int regionWidth;
    int regionHeight;
    float aspectRatio;
    float DPIScaleFactor;
    bool isInitiallyMinimized;
    bool isInitiallyMaxmized;
};

#endif