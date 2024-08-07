
#include "gApp.h"
#include "windowSystem.h"

void passKeyMessage(base_window& keyboardAccess,gAPP::gKey keyName,gAPP*, int vk_code_1, int vk_code_2 = -1) {
	
	keyboardAccess.mainKeyboard.setKey(vk_code_1);
	if (keyboardAccess.mainKeyboard.getState() == WinKeyboard::none) {
		
	}
}

int gAPP::run(gAPP* mainAPP) {

#ifdef _DEBUG_INFO_
	try {
		
		

	mainAPP->init();

	base_window gWindow(mainAPP->gName, mainAPP->width, mainAPP->height, -1, -1);

	while (base_window::getCountOfWindows() != 0) {
		mainAPP->tick();

		//mouse test
		if (gWindow.mainMouse.getLeftKeyState() == WinMouse::Pressed) {
			if (gWindow.getName() != "Pressed") gWindow.setTitle("Pressed");
		}
		else if (gWindow.mainMouse.getLeftKeyState() == WinMouse::Held) {
			if (gWindow.getName() != "Held") gWindow.setTitle("Held");
		}


		//Scroll test
		/*if (gWindow.mainMouse.getScrollDelta() == 0) {
			if (gWindow.getName() != "j") gWindow.setTitle("j");
		}
		else if (gWindow.mainMouse.getScrollDelta() > 0) {
			if (gWindow.getName() != "1") gWindow.setTitle("1");
		}
		else {
			if (gWindow.getName() != "-1") gWindow.setTitle("-1");
		}*/

		gWindow.mainMouse.reviewKeys();
		gWindow.processWindowTick();

	//base_window win2("win2");
		
		//switch (gWindow.mainMouse.getState()) {
		//case WinMouse::Pressed:
		//	if (gWindow.getName() != "PressedMouse") gWindow.setTitle("PressedMouse");
		//	break;
		//case WinMouse::Held: //TODO
		//	if (gWindow.getName() != "HeldMouse") gWindow.setTitle("HeldMouse");
		//	break;
		//case WinMouse::Released:
		//	if (gWindow.getName() != "ReleasedMouse") { 
		//		gWindow.setTitle("ReleasedMouse");
		//		Sleep(1000);
		//	}
		//	
		//	break;
		//default:
		//	if (gWindow.getName() != "None") gWindow.setTitle("None");
		//	break;
		

		// up(w) keys : 0x26 , 0x57 
		// left(a) keys : 0x25 , 0x41
		// down(s) keys : 0x28 , 0x53
		// right(d) keys : 0x27 , 0x44
	}

	delete mainAPP;

	return 0;
	}
	catch (std::exception& error) { OutputDebugStringA(error.what()); }
	catch (...) { OutputDebugStringA("Something went badly wrong"); }

#endif

	return -1;
}



