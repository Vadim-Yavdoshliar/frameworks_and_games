

#ifndef _WINDOW_
#define _WINDOW_

#include <Windows.h>


class base_window {

	static int windowCounter;
	const char* windowName;

public:

	base_window(const char*);

	~base_window();

public:

	const char* getName();
	int getCountOfWindows();

};


// class with only one instance of itself
class WNDCLASSconfig {

private:

	static WNDCLASSconfig mainClass; // single instance if current class

	WNDCLASSEXA* windowClassInst; // exact winAPI class

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
