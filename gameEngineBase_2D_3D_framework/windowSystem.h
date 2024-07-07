

#ifndef _WINDOW_
#define _WINDOW_

#include <Windows.h>
#include <list>

LRESULT  CustomProcForFramework(
	HWND   hWnd,
	UINT   Msg,
	WPARAM wParam,
	LPARAM lParam
);

class base_window {

	static int windowCounter;
	const char* windowName;
	HWND systemWindow = nullptr;

	static std::list<base_window*> listOfWindows;

	int X, Y;
	int width, height;

	virtual void processEvents(MSG&);

public:

	static void processWindows();
	base_window(const char*, int sizeX, int sizeY, int posX, int posY);
	virtual ~base_window();

public:

	const char* getName();
	static int getCountOfWindows();
	
	virtual void init();
	virtual void show();
	virtual void hide();


};


// class with only one instance of itself
class WNDCLASSconfig {

private:

	static WNDCLASSconfig mainClass; // single instance if current class

	WNDCLASSEXA windowClassInst; // exact winAPI class

	const char* WNDCLASSname = "baseWNDClass";
	
	HINSTANCE currHANDLER; // handler for all objects produced in this class

private:

	WNDCLASSconfig();

private:
	// ansure that the class cant be copied or moved
	WNDCLASSconfig(const WNDCLASSconfig&) = delete;
	WNDCLASSconfig(WNDCLASSconfig&&) = delete;
	WNDCLASSconfig operator=(const WNDCLASSconfig&) = delete;
	WNDCLASSconfig operator=(WNDCLASSconfig&&) = delete;

public:

	static const char* getWNDCLASSname();
	static HINSTANCE getMainHandler();
	~WNDCLASSconfig();
};


#endif // !_WINDOW_
