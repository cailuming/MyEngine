#include "Main.h"

CWindow *window = 0;

int _stdcall WinMain(HINSTANCE h, HINSTANCE pre, char *args, int style)
{
	window = CWindow::create(h, 0, 0, 800, 600, false);
 
	window->startPumpMessage();
}