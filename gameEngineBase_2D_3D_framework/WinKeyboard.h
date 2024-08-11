

#ifndef _KEYBOARD_
#define _KEYBOARD_

#include "_conditions.h"
#include "gApp.h"

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

#define DEF_KEY -100

class WinKeyboard {

public:


protected:

	struct Key {

		bool Pressed = 0;
		bool Released = 0;
		bool preventPress = 0;

		int virtualKeyValue;

	};

private:
	
	std::vector<WinKeyboard::Key> keyBuffer;
	Key* currentKey = nullptr;
	std::string textStream;
	bool textStreamOpened = 0;

	bool charScanned = 0;

public:

	void openStream();
	std::string closeStream();
	bool isStreamOpened() { return textStreamOpened; }
	int getLastFromStream();

	WinKeyboard();

	void setKey(int vk_code);
	bool isPressed();
	bool isReleased();
	
	void processKeyMessage(UINT, LPARAM, WPARAM);

};

void processKeyborad(gAPP*);

#endif