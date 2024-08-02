

#include "WinKeyboard.h"

// --------------------------------**
// <START> WinKeyboard             **
//         methods implementation  **
// --------------------------------**


WinKeyboard::WinKeyboard() : keyBuffer(256)
{
}

void WinKeyboard::setKey(int vk_code)
{
	if (vk_code == -1) {
		currentKey = Key();
		return;
	}
	if (vk_code > 0 && vk_code < 257) {
		currentKey = keyBuffer[vk_code - 1];
	}
}

WinKeyboard::keyState WinKeyboard::getState()
{
	return currentKey.state;
}


void WinKeyboard::processKeyMessage
(UINT msg, LPARAM lParam, WPARAM wParam)
{
	Key enteredKey;
	enteredKey.virtualKeyValue = wParam;
	if (msg == WM_KEYDOWN || msg == WM_SYSKEYDOWN)
	{
		enteredKey.state = Pressed;
		if (keyBuffer[(int)wParam - 1].state == enteredKey.state) { 
			
			keyBuffer[(int)wParam - 1].state = WinKeyboard::Held;
		}
		else {
			keyBuffer[(int)wParam - 1] = enteredKey;
		}
	}
	else if (msg == WM_KEYUP || msg == WM_SYSKEYUP)
	{
	    enteredKey.state = Released;
		keyBuffer[(int)wParam - 1] = enteredKey;
	}

	
}

void WinKeyboard::reviewKeys()
{
	for (auto& rkey : keyBuffer) {
		rkey.state = (rkey.state == Pressed) ? Held : rkey.state;
		rkey.state = (rkey.state == Released) ? none : rkey.state;
	}
}


// --------------------------------**
// <END> WinKeyboard               **
//         methods implementation  **
// --------------------------------**

