
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

	struct Key {

		mutable keyState state = none;
		int virtualKeyValue;

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
	Key currentKey;
	Coordinate mouseCoor;

public:

	WinMouse();

	/// <summary>
    /// Returns key state
    /// </summary>
    /// <returns></returns>
	keyState getState();

 	/// <summary>
    /// Returns mouse click coordinate
    /// </summary>
    /// <returns></returns>
	Coordinate getCoordinate();
	void processKeyMessage(UINT, LPARAM, WPARAM);
	void reviewKeys();
};


#endif