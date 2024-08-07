

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

void WinKeyboard::clearKey()
{
	keyBuffer[currentKey.virtualKeyValue - 1].state = WinKeyboard::none;
	currentKey.state = WinKeyboard::none;
}


void WinKeyboard::processKeyMessage
(UINT msg, LPARAM lParam, WPARAM wParam)
{
	Key enteredKey;
	enteredKey.virtualKeyValue = wParam;
	if (msg == WM_KEYDOWN || msg == WM_SYSKEYDOWN)
	{
		enteredKey.state = Pressed;
		if (keyBuffer[(size_t)wParam - 1].state == enteredKey.state) {
			
			keyBuffer[(size_t)wParam - 1].state = WinKeyboard::Held;
		}
		else if (keyBuffer[(size_t)wParam - 1].state != WinKeyboard::Held) {
			keyBuffer[(size_t)wParam - 1] = enteredKey;
		}
	}
	else if (msg == WM_KEYUP || msg == WM_SYSKEYUP)
	{
	    enteredKey.state = Released;
		keyBuffer[(size_t)wParam - 1] = enteredKey;
		if (keyBuffer[(size_t)wParam - 1].virtualKeyValue == currentKey.virtualKeyValue) {
			currentKey = keyBuffer[(size_t)wParam - 1];
		}
	}

	
}





// --------------------------------**
// <END> WinKeyboard               **
//         methods implementation  **
// --------------------------------**

