
#include "gApp.h"
#include "windowSystem.h"


void gAPP::openTextStream()
{
	base_window::gameWindow->mainKeyboard.openStream();
}
std::string gAPP::closeTextStream()
{
	
	return base_window::gameWindow->mainKeyboard.closeStream();
}

int gAPP::run(gAPP* mainAPP) {

	

#ifdef _DEBUG_INFO_
	try {

	mainAPP->initFrameworkResources();

	base_window gWindow(mainAPP->gName, mainAPP->width, mainAPP->height, -1, -1);

	base_window::gameWindow = &gWindow;

	mainAPP->init();

	//initPicture();

	while (base_window::getCountOfWindows() != 0) {
		
		mainAPP->tick();

		//drawTextureTest();

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





