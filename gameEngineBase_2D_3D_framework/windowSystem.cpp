


#include "windowSystem.h"


// -------------------------------------------------
// 
// <START> of the field for custom window PROCEDURES

base_window::windowState base_window::defBaseWindowProc
(UINT& msg, WPARAM wParam, LPARAM lParam)
{
	
	switch (msg) {
	case WM_DESTROY:
		return windowState::destroyed;
	}

	return windowState::processed;
}

LRESULT WINAPI base_window::baseWindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{

	for (auto& win : listOfWindows) {
		if (win != nullptr) {
			if (win->mainWindow == hWnd) {
				if (win->windowNextState != windowState::destroyed)
					win->windowNextState = win->customWinProc(Msg, wParam, lParam);
				else {
					delete win;
					win = nullptr;
				}
				break;
			}
		}
	}

	if (getCountOfWindows() == 0) PostQuitMessage(7);

	return DefWindowProcA(hWnd, Msg, wParam, lParam);
}

// <END> of of the field for custom window PROCEDURES
// 
// -------------------------------------------------




// ----------------------------------------
//                                        *
// <START> of defenition for base_window  *
//                                        *
// ----------------------------------------


std::list<base_window*> base_window::listOfWindows;





void base_window::processWindows()
{
	MSG message_inst;
	while (1) {

		GetMessageA(&message_inst, nullptr, 0, 0);
		TranslateMessage(&message_inst);
		DispatchMessageA(&message_inst);
		

		if (getCountOfWindows() == 0) {
			break;
		}
		
	}
}

base_window::base_window
(
	const char* windowName,
	int sizeX,
	int sizeY,
	int posX, 
	int posY,
	windowState(*WinProc)
	(UINT&, WPARAM, LPARAM)
) 
  : windowName(windowName), 
	width(sizeX), 
	height(sizeY), 
	X(posX), 
	Y(posY)
{

	listOfWindows.push_back(this);

	if (WinProc == nullptr) {
		customWinProc = base_window::defBaseWindowProc;
	}
}


base_window::~base_window()
{
	
}

void base_window::clearWindowList()
{
	for (auto& win : listOfWindows) {
		delete win;
	}
}

base_window* base_window::createBaseWindow(
	const char* windowName,
	int sizeX,
	int sizeY,
	int posX,
	int posY,
	windowState(*WinProc)
	(UINT&, WPARAM, LPARAM)
)
{
	return new base_window(windowName,sizeX,sizeY,posX,posY, WinProc);
}

const char* base_window::getName()
{
	return this->windowName;
}

int base_window::getCountOfWindows()
{
	int countOfWindows = 0;
	for (auto& win : listOfWindows) {
		if (win != nullptr) ++countOfWindows;
	}
	return countOfWindows;
}

void base_window::init()
{
	// [ FUNCTION SPECIFIC ]
	// Is virtual. Gives the opportunity to extend functional in derivative classes

	if (mainWindow != nullptr) {
		DestroyWindow(mainWindow);
	}

	// [ SCREEN DATA CATCHING ] 
	int screenSizeX = GetSystemMetrics(SM_CXSCREEN);
	int screenSizeY = GetSystemMetrics(SM_CYSCREEN);

	this->windowName = windowName;

	// [ INCORRECT COORDINATES ]
	// inapropriate input of position coordinates is excluded
	// and invokes an automatic reset of the position by placing 
	// a window in the center of the screen

	if (X < 0 || Y < 0 ||
		X > screenSizeX || Y > screenSizeY) {

		X = screenSizeX / 2;
		Y = screenSizeY / 2;
	}

	// [ INCORRECT SIZE DATA ]
	// Window size constrains are determined in the following way :
	// * min_Width = 100, min_height = 100;
	// * max and min sizes are the same as sizes of screen a user has
	// 
	// * default sizes are included when data entered incorrectly and equal the third part 
	//   of screen sides for every dimemsion of the window
	//	 width = screen_width / 3; height = screen_height / 3

	if (width < 100 || height < 100 ||
		width > screenSizeX || height > screenSizeY) {

		width = screenSizeX / 3;
		height = screenSizeY / 3;

	}

	mainWindow = CreateWindowExA
	(
		0,
		WNDCLASSconfig::getWNDCLASSname(),
		windowName,
		WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU | WS_OVERLAPPED | WS_CAPTION | WS_THICKFRAME,
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
	if(mainWindow != nullptr)
	ShowWindow(mainWindow, SW_SHOW);
	
}

void base_window::hide()
{
	if (mainWindow != nullptr)
	ShowWindow(mainWindow, SW_HIDE);
}

// ----------------------------------------
//                                        *
// <END> of defenition for base_window    *
//                                        *
// ----------------------------------------



// -------------------------------------------
//                                           *
// <START> of defenition for WNDCLASSconfig  *
//                                           *
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
	windowClassInst.style = CS_OWNDC;
	windowClassInst.lpfnWndProc = base_window::baseWindowProc;
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
//                                          *
// <END> of defenition for WNDCLASSconfig   *
//                                          *
// ------------------------------------------




