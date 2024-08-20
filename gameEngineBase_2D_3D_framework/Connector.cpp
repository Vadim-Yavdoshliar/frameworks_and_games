
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

	initSpriteCreation();

	Sprite* s = createSprite("chest_with_tongue_pixels.png");

	mainAPP->init();

	//initPicture();

	clock_t start = clock();

	
	while (base_window::getCountOfWindows() != 0) {
		
		gw_object->graphicsStation->startFrame();

		mainAPP->tick();

		//drawTextureTest();
		
		drawSprite(s, 0, 0);
		processMouse(&gWindow);
		processKeyborad(mainAPP);
		
		
		gWindow.processWindowTick();

		gw_object->graphicsStation->showFrame();
	}

	delete s;
	delete mainAPP;

	return 0;
	}
	catch (std::exception& error) { OutputDebugStringA(error.what()); }
	catch (...) { OutputDebugStringA("\n\n\n\nSomething went badly wrong\n\n\n\n"); }

#endif

	return -1;
}





