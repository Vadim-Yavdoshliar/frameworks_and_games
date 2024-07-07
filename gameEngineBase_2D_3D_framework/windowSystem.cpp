


#include "windowSystem.h"


// -------------------------------------------------
// 
// <START> of the field for custom window PROCEDURES

LRESULT WINAPI CustomProcForFramework(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{

	if (Msg == WM_CLOSE) PostQuitMessage(3);

	return DefWindowProcA(hWnd, Msg, wParam, lParam);
}

// <END> of of the field for custom window PROCEDURES
// 
// -------------------------------------------------




// ----------------------------------------
//										  *
// <START> of defenition for base_window  *
//										  *
// ----------------------------------------

int base_window::windowCounter = 0;
std::list<base_window*> base_window::listOfWindows;

void base_window::processEvents(MSG& msg_inst)
{
	if (this->systemWindow != nullptr) {
		GetMessageA(&msg_inst, this->systemWindow, 0, 0);
		TranslateMessage(&msg_inst);
		DispatchMessageA(&msg_inst);
	}
}

void base_window::processWindows()
{
	MSG message_inst;
	while (1) {
		for (auto& win : listOfWindows) {
			win->processEvents(message_inst);
		}
		
	}
}

base_window::base_window
(
	const char* windowName,
	int sizeX,
	int sizeY,
	int posX, 
	int posY
) 
  : windowName(windowName), 
	width(sizeX), 
	height(sizeY), 
	X(posX), 
	Y(posY)
{

	listOfWindows.push_back(this);

}

base_window::~base_window()
{
	listOfWindows.remove(this);
}

const char* base_window::getName()
{
	return this->windowName;
}

int base_window::getCountOfWindows()
{
	return windowCounter;
}

void base_window::init()
{

	int screenSizeX = GetSystemMetrics(SM_CXSCREEN);
	int screenSizeY = GetSystemMetrics(SM_CYSCREEN);

	this->windowName = windowName;
	if (X < 0 || Y < 0 ||
		X > screenSizeX || Y > screenSizeY) {

		X = screenSizeX / 2;
		Y = screenSizeX / 2;
	}

	if (width < 100 || height < 100 ||
		width > screenSizeX || height > screenSizeY) {

		width = screenSizeX / 3;
		height = screenSizeY / 3;

	}

	systemWindow = CreateWindowExA
	(
		0,
		WNDCLASSconfig::getWNDCLASSname(),
		windowName,
		WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU,
		X,
		Y,
		width,
		height,
		nullptr,
		nullptr,
		WNDCLASSconfig::getMainHandler(),
		nullptr
	);

}

void base_window::show()
{
	if(systemWindow != nullptr)
	ShowWindow(systemWindow, SW_SHOW);
	
}

void base_window::hide()
{
	if (systemWindow != nullptr)
	ShowWindow(systemWindow, SW_HIDE);
}

// ----------------------------------------
//										  *
// <END> of defenition for base_window    *
//										  *
// ----------------------------------------



// -------------------------------------------
//											 *
// <START> of defenition for WNDCLASSconfig  *
//											 *
// -------------------------------------------

WNDCLASSconfig WNDCLASSconfig::mainClass;

const char* WNDCLASSconfig::getWNDCLASSname()
{
	return mainClass.WNDCLASSname;
}

HINSTANCE WNDCLASSconfig::getMainHandler()
{
	return mainClass.currHANDLER;
}



WNDCLASSconfig::WNDCLASSconfig() {

	currHANDLER = GetModuleHandleA(nullptr);

	windowClassInst.cbSize = sizeof(windowClassInst);
	windowClassInst.style = CS_OWNDC | CS_DBLCLKS;
	windowClassInst.lpfnWndProc = CustomProcForFramework;
	windowClassInst.hInstance = currHANDLER;
	windowClassInst.cbClsExtra = 0;
	windowClassInst.cbWndExtra = 0;
	windowClassInst.hIcon = nullptr;
	windowClassInst.hCursor = nullptr;
	windowClassInst.hbrBackground = nullptr;
	windowClassInst.lpszMenuName = nullptr;
	windowClassInst.lpszClassName = WNDCLASSname;
	windowClassInst.hIconSm = nullptr;

	RegisterClassExA(&windowClassInst);
}


WNDCLASSconfig::~WNDCLASSconfig()
{
	UnregisterClassA(WNDCLASSname, currHANDLER);
}

// ------------------------------------------
//											*
// <END> of defenition for WNDCLASSconfig	*
//											*
// ------------------------------------------




