
#include "gApp.h"
#include "windowSystem.h"

int gAPP::run(gAPP* mainAPP) {
#ifdef _DEBUG_INFO_
	try {
	mainAPP->init();

	base_window gWindow(mainAPP->gName, mainAPP->width, mainAPP->height, -1, -1);
	while (base_window::getCountOfWindows() != 0) {
		mainAPP->tick();

		//mouse test
		/*if (gWindow.mainMouse.getLeftKeyState() == WinMouse::Pressed) {
			if (gWindow.getName() != "Pressed") gWindow.setTitle("Pressed");
		}
		else if (gWindow.mainMouse.getLeftKeyState() == WinMouse::Held) {
			if (gWindow.getName() != "Held") gWindow.setTitle("Held");
		}*/


		//Scroll test
		if (gWindow.mainMouse.getScrollDelta() == 0) {
			if (gWindow.getName() != "0") gWindow.setTitle("0");
		}
		else if (gWindow.mainMouse.getScrollDelta() > 0) {
			if (gWindow.getName() != "1") gWindow.setTitle("1");
		}
		else {
			if (gWindow.getName() != "-1") gWindow.setTitle("-1");
		}

		gWindow.mainMouse.reviewKeys();
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



