
#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#endif

#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp))
#endif
#ifndef _MOUSE_
#define _MOUSE_


#include "_conditions.h"
#include "gApp.h"

class WinMouse {

public:

	enum keyState {
		LPressed,
		LReleased,
		RPressed,
		RReleased,
		MPressed,
		MReleased,
		SidePressed,
		SideReleased,
		WheelUp,
		WheelDown,
		none
	};

protected:
	/// <summary>
	/// X and y coordinate
	/// </summary>
	struct Coordinate {
		int x;
		int y;
	};
	
private:
	int MAXBUFFERSIZE = 50;
	std::queue<keyState> buffer;
	int scrollDelta = 0;
	Coordinate mouseCoordinate;

public:
	bool mouseIsAvailable = true;

public:

	WinMouse();

	Coordinate getMouseCoordinate();
	int getXmouseCoordinate();
	int getYmouseCoordinate();

	bool isLButtonPressed();
	bool isLButtonReleased();

	bool isRButtonPressed();
	bool isRButtonReleased();

	bool isSideButtonPressed();
	bool isSideButtonReleased();

	bool isMButtonPressed();
	bool isMButtonReleased();

	bool isWheelUp();
	bool isWheelDown();

	void processKeyMessage(UINT, LPARAM, WPARAM);


private:
	void clearBuffer();
	void OnPressed(keyState key);
	void OnReleased(keyState key);
	void IfBufferIsFool();
};

void processMouse(base_window*);

#endif