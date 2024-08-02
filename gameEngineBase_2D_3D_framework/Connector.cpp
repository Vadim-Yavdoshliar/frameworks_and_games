
#include "gApp.h"
#include "windowSystem.h"

int gAPP::run(gAPP* mainAPP) {

	mainAPP->init();

	base_window gWindow(mainAPP->gName, mainAPP->width, mainAPP->height, -1, -1);
	
	while (base_window::getCountOfWindows() != 0) {
		mainAPP->tick();
		gWindow.processWindowTick();
	}

	delete mainAPP;

	return 0;
}