

#ifndef _KEYBOARD_
#define _KEYBOARD_

#include "_conditions.h"

class WinKeyboard {

public:

	enum keyState {
		Pressed,
		Held,
		Released,
		none
	};

protected:

	struct Key {

		keyState state = none;

		char letter = '\0';
		int virtualKeyValue;
	};

private:

	std::set<WinKeyboard::Key> keyBuffer;
	Key currentKey;

public:

	char getChar();
	int getKey();
	Key getState();
	void setNext();




};

#endif