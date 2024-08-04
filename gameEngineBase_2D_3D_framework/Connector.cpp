
#include "gApp.h"
#include "windowSystem.h"

int gAPP::run(gAPP* mainAPP) {
#ifdef _DEBUG_INFO_
	try {
	mainAPP->init();

	base_window gWindow(mainAPP->gName, mainAPP->width, mainAPP->height, -1, -1);
	base_window win2("win2");
	while (base_window::getCountOfWindows() != 0) {
		mainAPP->tick();
		gWindow.processWindowTick();
		win2.processWindowTick();
	}

	delete mainAPP;

	return 0;
	}
	catch (std::exception& error) { OutputDebugStringA(error.what()); }
	catch (...) { OutputDebugStringA("Something went badly wrong"); }

#endif

	return -1;
}



