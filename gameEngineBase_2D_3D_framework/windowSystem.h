

#ifndef _WINDOW_
#define _WINDOW_



#include "WinKeyboard.h"
#include "WinMouse.h"
#include "graphicsControl.h"

#define WindowProcedureFunction(name) void WINAPI name(base_window& win ,UINT& msg, WPARAM wp, LPARAM lp)


void drawTextureTest();

class base_window {

public:
	static base_window* gameWindow;

	graphicsControl* graphicsStation = nullptr;
	
	static const int screenSizeX;
	static const int screenSizeY;

private:
	
	// Includes all windows with not null HWND mainWindow field 
	// (whether the window is hidden or not)
	static int countOfFilledWindows;

	// Default window procedure, it's automatically set up for window
	// where the custom window procedure hasn't been passed 
	static void WINAPI defBaseWindowProc
	(base_window&,UINT&, WPARAM, LPARAM);

	// Pointer to the custom window procedure of the window. 
	// Acts as the element to obtain unique window procedure for every window
	void(WINAPI*customWinProc) (base_window&,UINT&, WPARAM, LPARAM);

	// Window name and window pointer
	std::string windowName;
	HWND mainWindow = nullptr;
	HWND parentWindow = nullptr;

	static std::vector<base_window*> listOfWindows;

	int X, Y; // Window position
	int width, height;

	

public:

	WinKeyboard mainKeyboard;
	WinMouse mainMouse;

	base_window(
		const char*, 
		int sizeX = 0,
		int sizeY = 0, 
		int posX = -1, 
		int posY = -1,
		base_window* parent = nullptr,
		void(WINAPI*WinProc)
		(base_window&, UINT&, WPARAM, LPARAM) = nullptr);

	base_window(const base_window&) = delete;
	base_window(base_window&&) = delete;
	base_window* operator=(const base_window&) = delete;

public:

	static LRESULT WINAPI baseWindowProc(
		HWND hWnd,
		UINT Msg,
		WPARAM wParam,
		LPARAM lParam
	);


	static void processWindows();
	void processWindowTick();
	
	virtual ~base_window();


public:

	static void clearWindowList();

	const char* getName();
	HWND getWND() { return mainWindow; }
	static int getCountOfWindows();
	

	virtual void init();
	virtual void show();
	virtual void hide();
	virtual void setPosition(int x,int y);
	virtual void setSize(int width, int height);
	virtual void setTitle(const char*);
	virtual void destroy();

	int getWidth() { return width; }
	int getHeight() { return height; }

	int getPosX() { return X; }
	int getPosY() { return Y; }

};


// (SINGLETON) class for auto registering win32 window class
class WNDCLASSconfig {

private:

	static WNDCLASSconfig mainClass; // single instance of current class

	WNDCLASSEXA windowClassInst; // exact winAPI class

	const char* WNDCLASSname = "baseWNDClass";
	
	HINSTANCE currHANDLER; // handler for all objects produced with this class

private:

	WNDCLASSconfig();

private:
	// ansure that the class can't be copied or moved
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
