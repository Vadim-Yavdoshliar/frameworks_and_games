

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

private:

	std::vector<WinMouse::Key> keyBuffer;
	Key currentKey;

public:

	WinMouse();

	void setKey(int vk_code);
	keyState getState();

	void processKeyMessage(UINT, LPARAM, WPARAM);
	void reviewKeys();
};


#endif