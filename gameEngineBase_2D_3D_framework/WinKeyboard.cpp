

#include "windowSystem.h"


// --------------------------------**
// <START> WinKeyboard             **
//         methods implementation  **
// --------------------------------**

#define NO_INPUT -1

WinKeyboard::WinKeyboard() : keyBuffer(256)
{
}

void WinKeyboard::setKey(int vk_code)
{

	if (vk_code > -1 && vk_code < 257) {
		currentKey = &keyBuffer[vk_code - 1];
	}
	else {
		currentKey = nullptr;
	}
}

bool WinKeyboard::isPressed()
{
	if (currentKey == nullptr)return 0;
	bool res = currentKey->Pressed;
	currentKey->Pressed = 0;
	return res;
}

bool WinKeyboard::isReleased()
{
	if (currentKey == nullptr)return 0;
	bool res = currentKey->Released;
	currentKey->Released = 0;
	return res;
}


void WinKeyboard::openStream() {
	textStreamOpened = 1;
}

std::string WinKeyboard::closeStream() {
	textStreamOpened = 0;
	std::string temp = textStream;
	textStream.clear();
	return temp;
}

int WinKeyboard::getLastFromStream()
{
	if (textStream.size() == 0 || (!charScanned)) 
		return NO_INPUT;
	else {
		charScanned = 0;
		return textStream[textStream.size() - 1]; 
	}
}

void WinKeyboard::processKeyMessage
(UINT msg, LPARAM lParam, WPARAM wParam)
{
	
	if (msg == WM_CHAR) {
		if (textStreamOpened) {
			if (wParam == 0x08) {
				textStream.erase(textStream.size() - 1);
				charScanned = 0;
			}
			else {
				textStream += (char)wParam;
				charScanned = 1;
			}
		}
	}
	if (msg == WM_KEYDOWN || msg == WM_SYSKEYDOWN)
	{
		keyBuffer[wParam - 1].virtualKeyValue = wParam;
		if (!keyBuffer[wParam - 1].preventPress) {
			keyBuffer[wParam - 1].Pressed = 1;
			keyBuffer[wParam - 1].Released = 0;
			keyBuffer[wParam - 1].preventPress = 1;
		}
		
	}
	else if (msg == WM_KEYUP || msg == WM_SYSKEYUP)
	{
		keyBuffer[wParam - 1].virtualKeyValue = wParam;
		keyBuffer[wParam - 1].Pressed = 0;
		keyBuffer[wParam - 1].Released = 1;
		keyBuffer[wParam - 1].preventPress = 0;
	}
	
}


void sendKey(gAPP* app ,gAPP::gKey desiredKey,int vk_1, int vk_2 = -1) {
	
	base_window::gameWindow->mainKeyboard.setKey(vk_1);
	bool kPress_1 = base_window::gameWindow->mainKeyboard.isPressed();
	bool kRelease_1 = base_window::gameWindow->mainKeyboard.isReleased();

	base_window::gameWindow->mainKeyboard.setKey(vk_2);
	bool kPress_2 = base_window::gameWindow->mainKeyboard.isPressed();
	bool kRelease_2 = base_window::gameWindow->mainKeyboard.isReleased();

	if (kPress_1||kPress_2)
		app->gKeyPressed(desiredKey);
	else if (kRelease_1||kRelease_2)
		app->gKeyReleased(desiredKey);

}

//#define _INPUT_TEST_



void processKeyborad(gAPP* app) {	
		
#ifdef _INPUT_TEST_

	base_window::gameWindow->mainKeyboard.setKey(0x57);

	if(base_window::gameWindow->mainKeyboard.isPressed()){
		if (*base_window::gameWindow->getName() != 'P') {
			base_window::gameWindow->setTitle("Pressed");
			Sleep(200);
		}
	}
	else if (base_window::gameWindow->mainKeyboard.isReleased()) {
		if (*base_window::gameWindow->getName() != 'R') {
			base_window::gameWindow->setTitle("Released");
			Sleep(100);
		}
	}
	else {
		if (*base_window::gameWindow->getName() != 'N')
			base_window::gameWindow->setTitle("None");
	}
#endif

	int initialState = gAPP::ForwardKey;
	//int initialState = -1;
	

    if (initialState == 0){ 
	sendKey(app, (gAPP::gKey)initialState, 0x57, 0x26);
	++initialState;
	}
	if (initialState == 1) {
		sendKey(app, (gAPP::gKey)initialState, 0x53, 0x28);
		++initialState;
	}
	if (initialState == 2) {
		sendKey(app, (gAPP::gKey)initialState, 0x41, 0x25);
		++initialState;
	}
	if (initialState == 3) {
		sendKey(app, (gAPP::gKey)initialState, 0x44, 0x27);
		++initialState;
	}
	if (initialState == 4) {
		sendKey(app, (gAPP::gKey)initialState, 0x20);
		++initialState;
	}
	if (initialState == 5) {
		sendKey(app, (gAPP::gKey)initialState, 0x10);
		++initialState;
	}
	if (initialState == 6) {
		sendKey(app, (gAPP::gKey)initialState, 0x11);
		++initialState;
	}
	if (initialState == 7) {
		sendKey(app, (gAPP::gKey)initialState, 0x09);
		++initialState;
	}
	if (initialState == 8) {
		sendKey(app, (gAPP::gKey)initialState, 0x1B);
		++initialState;
	}
	if (initialState == 9) {
		sendKey(app, (gAPP::gKey)initialState, 0x08);
		++initialState;
	}
	if (initialState == 10) {
		sendKey(app, (gAPP::gKey)initialState, 0x0D);
		++initialState;
	}

	if (base_window::gameWindow->
		mainKeyboard.isStreamOpened()) {
		int res = base_window::gameWindow->
			mainKeyboard.getLastFromStream();
		if (res != NO_INPUT)
			app->charInput(res);
	}
}



// --------------------------------**
// <END> WinKeyboard               **
//         methods implementation  **
// --------------------------------**

