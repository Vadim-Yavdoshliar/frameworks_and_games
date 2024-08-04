


#include "windowSystem.h"


// -------------------------------------------------
// 
// <START> of the field for custom window PROCEDURES
// 
// -------------------------------------------------
void WINAPI base_window::defBaseWindowProc
(base_window& win,UINT& msg, WPARAM wParam, LPARAM lParam)
{
	
	win.mainKeyboard.setKey(0x57);
	if (win.mainKeyboard.getState() != WinKeyboard::none) {
		if (win.mainKeyboard.getState() == WinKeyboard::Pressed) {
			if (win.windowName != "Abracadabra") {
			win.setTitle("Abracadabra");
			}
		}
			
	}
	else {
		if (win.windowName != "Nothing happening") {
			win.setTitle("Nothing happening");
		}
	}

}

LRESULT WINAPI base_window::baseWindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{


	if (Msg == WM_CREATE) {
		
		CREATESTRUCTA* createStructOfWindow = reinterpret_cast<CREATESTRUCTA*>(lParam);
		SetWindowLongPtrA(
			hWnd, 
			GWLP_USERDATA,
			reinterpret_cast<LONG_PTR>(createStructOfWindow->lpCreateParams)
		);
		++countOfFilledWindows;
		
	}
	else {
	
		if (Msg == WM_DESTROY)
			--countOfFilledWindows;
		base_window* windowInst = reinterpret_cast<base_window*>(GetWindowLongPtrA(hWnd, GWLP_USERDATA));
		if (windowInst != nullptr) {
			windowInst->mainKeyboard.processKeyMessage(Msg, lParam, wParam);
			windowInst->customWinProc(*windowInst, Msg, wParam, lParam);
			windowInst->mainKeyboard.reviewKeys();
		}
	}
	


	return DefWindowProcA(hWnd, Msg, wParam, lParam);
}
// --------------------------------------------------
// 
// <END> of of the field for custom window PROCEDURES
// 
// --------------------------------------------------




// ----------------------------------------
//                                        *
// <START> of defenition for base_window  *
//                                        *
// ----------------------------------------



std::vector<base_window*> base_window::listOfWindows;

int base_window::countOfFilledWindows = 0;

const int base_window::screenSizeX = GetSystemMetrics(SM_CXSCREEN);
const int base_window::screenSizeY = GetSystemMetrics(SM_CYSCREEN);


void base_window::processWindows()
{

	MSG message_inst;
	while (1) {
		while (PeekMessageA(&message_inst, nullptr, 0, 0,PM_REMOVE)) {

			TranslateMessage(&message_inst);
			DispatchMessageA(&message_inst);
		}

		for(auto win : listOfWindows)
				if(win!=nullptr)SendMessageA(win->getWND(), WM_USER + 1, 0, 0);
	
		if (getCountOfWindows() == 0)break;
		
		Sleep(1);
	}

}

base_window::base_window
(
	const char* windowName,
	int sizeX,
	int sizeY,
	int posX, 
	int posY,
	base_window* parent,
	void(WINAPI*WinProc)
	(base_window&,UINT&, WPARAM, LPARAM)
) 
  : windowName(windowName), 
	width(sizeX), 
	height(sizeY), 
	X(posX), 
	Y(posY)
{


	if (WinProc == nullptr) {
		customWinProc = base_window::defBaseWindowProc;
	}
	else {
		customWinProc = WinProc;
	}

	if (parent != nullptr) {
		parentWindow = parent->mainWindow;
	}

	init();
	show();

	listOfWindows.push_back(this);

	if (mainWindow != nullptr)
		graphicsStation = new graphicsControl(this);
}


base_window::~base_window()
{
	if (mainWindow != nullptr) {
		DestroyWindow(mainWindow);
	}

	delete graphicsStation;
}

void base_window::processWindowTick()
{
	MSG message_inst;
		while (PeekMessageA(&message_inst, mainWindow, 0, 0, PM_REMOVE)) {

			TranslateMessage(&message_inst);
			DispatchMessageA(&message_inst);
		}

		SendMessageA(mainWindow, WM_USER + 1, 0, 0);

		if(graphicsStation!=nullptr)
			graphicsStation->showFrame();
		
		Sleep(10);
}

void base_window::clearWindowList()
{
	listOfWindows.clear();
}

const char* base_window::getName()
{
	return this->windowName.c_str();
}

int base_window::getCountOfWindows()
{
	
	return countOfFilledWindows;
}

void base_window::init()
{
	// [ FUNCTION SPECIFIC ]
	// Is virtual. init() function can be overriden for extending or changing the
	// window initilisation in derivative classes

	if (mainWindow != nullptr) {
		DestroyWindow(mainWindow);
	}

	// [ SCREEN DATA CATCHING ] 

	this->windowName = windowName;

	// [ INCORRECT COORDINATES CASE ]
	// inapropriate input of position coordinates is excluded
	// and invokes an automatic reset of the position by placing 
	// a window in the center of the screen

	if (X < 0 || Y < 0 ||
		X > screenSizeX || Y > screenSizeY) {

		X = screenSizeX / 2;
		Y = screenSizeY / 2;
	}

	// [ INCORRECT SIZE DATA CASE ]
	// Window size constrains are determined in the following way :
	// * min_Width = 100, min_height = 100;
	// * max sizes are the same as sizes of user's screen
	// 
	// * default sizes are included when data entered incorrectly and equal to the third part 
	//   of a screen sides for every dimemsion of the window
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
		windowName.c_str(),
		WS_MINIMIZEBOX | WS_SYSMENU | WS_OVERLAPPED | WS_CAPTION,
		X,
		Y,
		width,
		height,
		parentWindow,
		nullptr,
		WNDCLASSconfig::getMainHandler(),
		this
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

void base_window::setPosition(int x,int y)
{
	if (x > -1 && x < screenSizeX + 1
		&& y > -1 && y < screenSizeY + 1) {
	
		this->X = x;
		this->Y = y;

		SetWindowPos(
			mainWindow
			, HWND_TOP
			, x
			, y
			, width
			, height
			, SWP_SHOWWINDOW | SWP_NOSIZE
		);
	}
}

void base_window::setSize(int width, int height)
{
	if (width < 100 || height < 100 ||
		width > screenSizeX || height > screenSizeY) {

		width = screenSizeX / 3;
		height = screenSizeY / 3;

	}
	else {
		this->width = width;
		this->height = height;

		SetWindowPos(
			mainWindow
			, HWND_TOP
			, X
			, Y
			, width
			, height
			, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_DRAWFRAME
		);
	}
}

void base_window::setTitle(const char* newTitle)
{
	windowName = newTitle;
	SetWindowTextA(mainWindow, windowName.c_str());
}

void base_window::destroy()
{
	DestroyWindow(mainWindow);
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
	windowClassInst.cbClsExtra = sizeof(base_window);
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




