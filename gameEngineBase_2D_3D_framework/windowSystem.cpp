


#include "windowSystem.h"

// =====================================
//									   *
// <START> defenition for base_window  *
//									   *
// =====================================

int base_window::windowCounter = 0;

base_window::base_window(const char* windowName) {
	this->windowName = windowName;
	CreateWindowExA()
}

const char* base_window::getName()
{
	return this->WindowName;
}

int base_window::getCountOfWindows()
{
	return windowCounter;
}

// =====================================
//									   *
// <END> defenition for base_window    *
//									   *
// =====================================



// ========================================
//									      *
// <START> defenition for WNDCLASSconfig  *
//									      *
// ========================================

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

	windowClassInst = new WNDCLASSEXA;

	windowClassInst->cbSize = sizeof(windowClassInst);
	windowClassInst->style = CS_OWNDC | CS_DBLCLKS;
	windowClassInst->lpfnWndProc = DefWindowProc;
	windowClassInst->hInstance = currHANDLER;
	windowClassInst->hIcon = nullptr;
	windowClassInst->hCursor = nullptr;
	windowClassInst->hbrBackground = nullptr;
	windowClassInst->lpszMenuName = nullptr;
	windowClassInst->lpszClassName = WNDCLASSname;
	windowClassInst->hIconSm = nullptr;

	RegisterClassExA(windowClassInst);
}


WNDCLASSconfig::~WNDCLASSconfig()
{
	UnregisterClassA(WNDCLASSname, currHANDLER);
	delete windowClassInst;
}

// ======================================
//										*
// <END> defenition for WNDCLASSconfig	*
//										*
// ======================================