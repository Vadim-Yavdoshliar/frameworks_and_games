

#ifndef _KEYBOARD_
#define _KEYBOARD_

#include "_conditions.h"

// ********************************
// ------------------------------**
//                               **
// WinKeyboard workflow diagram  **
//                               **
// ------------------------------**
// ********************************


/*

   |-----------------|               |-------------------|
   |                 |  Passing msg  |                   |
   | Vector of keys  <---------------| Window (C++ side) |
   |                 |               |                   |
   |------/\---------|               |-------------------|
          |
          |
          |
   |------|---------------------|
   |                            |
   | One key for getting data   |
   |                            |
   |------/\--------------------|
          |
          |
          |
   |------|----------------|
   |                       |
   |  Methods to interact  |
   |  with choosen key     |
   |                       |
   |-----------------------|

*/

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

		mutable keyState state = none;

		int virtualKeyValue;

	};

private:
	
	std::vector<WinKeyboard::Key> keyBuffer;
	Key currentKey;

public:

	WinKeyboard();

	void setKey(int vk_code);
	keyState getState();
	
	void processKeyMessage(UINT, LPARAM, WPARAM);
	void reviewKeys();
};

#endif