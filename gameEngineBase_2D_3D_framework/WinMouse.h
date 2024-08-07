
#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#endif

#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp))
#endif
#ifndef _MOUSE_
#define _MOUSE_


#include "_conditions.h"

class WinMouse {

public:

	enum keyState {
		Pressed,
		Held,
		Released,
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

protected:

	struct Key {

		mutable keyState state = none;
		int virtualKeyValue;
	};

private:
	Key rightKey;
	Key leftKey;
	Key middleKey;
	Key sideKey;
	
private:
	int scrollDelta = 0;
	Coordinate keyCoordinate;

public:

	WinMouse();

	keyState getRightKeyState();
	keyState getLeftKeyState();
	keyState getMiddleKeyState();
	keyState getSideKeyState();

	Coordinate getMouseCoordinate();

	int getScrollDelta();
	void processKeyMessage(UINT, LPARAM, WPARAM);
	void reviewKeys();

};


#endif