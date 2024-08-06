
#include "gApp.h"
#include "windowSystem.h"

int gAPP::run(gAPP* mainAPP) {

#ifdef _DEBUG_INFO_
	try {
		
		

	mainAPP->init();

	base_window gWindow(mainAPP->gName, mainAPP->width, mainAPP->height, -1, -1);
	//base_window win2("win2");
	while (base_window::getCountOfWindows() != 0) {
		mainAPP->tick();
		
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

		
		gWindow.mainKeyboard.setKey(0x57);

		
		if (gWindow.mainKeyboard.getState() == WinKeyboard::Released) {

		// some actions 
			Sleep(500);

			gWindow.mainKeyboard.clearKey();
		}

		gWindow.processWindowTick();
		
	}

	delete mainAPP;

	return 0;
	}
	catch (std::exception& error) { OutputDebugStringA(error.what()); }
	catch (...) { OutputDebugStringA("Something went badly wrong"); }

#endif

	return -1;
}



