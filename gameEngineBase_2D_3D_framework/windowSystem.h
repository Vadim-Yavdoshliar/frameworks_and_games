

#ifndef _WINDOW_
#define _WINDOW_

#include <Windows.h>
#include <list>
#include <ctime>


class base_window {

public:

	enum action {
		show_,
		hide_,
		destroy,
	};

private:

	static int countOfFilledWindows;

	static void defBaseWindowProc
	(base_window&,UINT&, WPARAM, LPARAM);

	void(*customWinProc) (base_window&,UINT&, WPARAM, LPARAM);

	const char* windowName;
	HWND mainWindow = nullptr;

	static std::list<base_window*> listOfWindows;

	int X, Y;
	int width, height;

public:

	base_window(
		const char*, 
		int sizeX = 0,
		int sizeY = 0, 
		int posX = -1, 
		int posY = -1,
		void(*WinProc)
		(base_window&, UINT&, WPARAM, LPARAM) = nullptr);

	

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
