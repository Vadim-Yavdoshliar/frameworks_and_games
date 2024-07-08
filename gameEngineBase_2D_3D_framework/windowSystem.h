

#ifndef _WINDOW_
#define _WINDOW_

#include <Windows.h>
#include <list>



class base_window {

	enum windowState {
	processed,
	destroyed
	};

	static windowState defBaseWindowProc
	(UINT&, WPARAM, LPARAM);

	windowState(*customWinProc) (UINT&, WPARAM, LPARAM);

	const char* windowName;
	HWND mainWindow = nullptr;

	static std::list<base_window*> listOfWindows;

	int X, Y;
	int width, height;

	virtual void processEvents(MSG&);

protected:

	base_window(
		const char*, 
		int sizeX, 
		int sizeY, 
		int posX, 
		int posY,
		windowState(*WinProc)
		(UINT&, WPARAM, LPARAM));

	

public:

	static LRESULT WINAPI baseWindowProc(
		HWND hWnd,
		UINT Msg,
		WPARAM wParam,
		LPARAM lParam
	);

	static void processWindows();
	
	virtual ~base_window();


public:

	static void clearWindowList();
	static base_window* createBaseWindow(
		const char*,
		int sizeX,
		int sizeY,
		int posX, 
		int	posY,
		windowState(*WinProc)
		(UINT&, WPARAM, LPARAM) = nullptr);

	const char* getName();
	static int getCountOfWindows();
	
	virtual void init();
	virtual void show();
	virtual void hide();

};

class testDerivedWindow : public base_window {
public:
	
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
