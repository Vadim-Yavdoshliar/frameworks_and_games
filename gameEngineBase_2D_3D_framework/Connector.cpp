
#include "gApp.h"
#include "windowSystem.h"


int gAPP::run(gAPP* mainAPP) {

	void drawTextureTest();

#ifdef _DEBUG_INFO_
	try {
		
		

	mainAPP->init();

	base_window gWindow(mainAPP->gName, mainAPP->width, mainAPP->height, -1, -1);

	gameWindow = &gWindow;

	while (base_window::getCountOfWindows() != 0) {
		
		mainAPP->tick();

		drawTextureTest();

		processMouse(mainAPP);
		processKeyborad(mainAPP);

		
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



