#include "CWindow.h"

CWindow::CWindow()
{
    memset(this, 0, sizeof(*this));
}

CWindow::~CWindow()
{
}

const char *CWindow::AppWindowClass = "CWindow";

CWindow *CWindow::cWindow = nullptr;
bool CWindow::isRunning = true;

MSG CWindow::msg;

CWindow *CWindow::create(HINSTANCE h, int posX, int posY, int width, int height, bool full)
{
    if (!cWindow)
    {
        cWindow = new CWindow();
        cWindow->initWindow(h, posX, posY, width, height, full);
    }

    return cWindow;
}

void CWindow::initWindow(HINSTANCE h, int posX, int posY, int width, int height, bool full)
{
    WNDCLASSEX wnd;
    memset(&wnd, 0, sizeof(wnd));
    wnd.cbClsExtra = 0;
    wnd.cbSize = sizeof(wnd);
    wnd.cbWndExtra = 0;
    wnd.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wnd.hCursor = LoadCursor(0, IDC_ARROW);
    wnd.hIcon = LoadIcon(0, IDI_APPLICATION);
    wnd.hIconSm = LoadIcon(0, IDI_APPLICATION);
    wnd.hInstance = h;
    wnd.lpfnWndProc = WinProc;
    wnd.lpszClassName = AppWindowClass;
    wnd.lpszMenuName = 0;
    wnd.style = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClassEx(&wnd))
    {
        MessageBox(0, "Failed to register window class!", 0, 0);
        return;
    }

    int tempWidth;
    int tempHeight;
    int tempFlag;

    if (full)
    {
        tempWidth = width;
        tempHeight = height;
        tempFlag = WS_EX_TOPMOST | WS_POPUP;
    }
    else
    {
        tempWidth = width + ::GetSystemMetrics(SM_CXBORDER) * 2;
        tempHeight = height + ::GetSystemMetrics(SM_CYCAPTION);
        tempFlag = WS_SYSMENU | WS_MINIMIZEBOX;
    }

    hwnd = CreateWindowExA(0, AppWindowClass, "BlankTitle", tempFlag, posX, posY, tempWidth, tempHeight, 0, 0, h, 0);

    if (!hwnd)
    {
        MessageBoxA(0, "Failed to create the window!", 0, 0);
        return;
    }
   
};

void CWindow::startPumpMessage(void(*renderFunc)(int delta))
{
    ::ShowWindow(hwnd, SW_NORMAL);
    while (isRunning)
    {
        if (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
			if (timer->canGo(30)) {
				renderFunc(timer->getTickDelta());
			}	 
        }
    }
};
 
LRESULT CALLBACK CWindow::WinProc(HWND hwnd, UINT msgID, WPARAM wp, LPARAM lp)
{
    switch (msgID)
    {
    case WM_CREATE:
        isRunning = true;
        break;
    case WM_CLOSE:
		isRunning = false;
        break;
    }
    return DefWindowProc(hwnd, msgID, wp, lp);
};

HWND CWindow::getWindowHwnd() {
	return hwnd;
};