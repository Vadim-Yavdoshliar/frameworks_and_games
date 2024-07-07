
#include "windowSystem.h"

int WINAPI WinMain(HINSTANCE handler, HINSTANCE someTrashMaybe, LPSTR cmdParams, int wndStatus) {
	
	base_window a("newWin",500,500,500,500);
	a.init();
	a.show();

	base_window::processWindows();



	return 0;
}