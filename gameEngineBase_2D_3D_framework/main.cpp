
#include "windowSystem.h"

int WINAPI WinMain(HINSTANCE handler, HINSTANCE someTrashMaybe, LPSTR cmdParams, int wndStatus) {
	
	base_window* a = 
		base_window::createBaseWindow("newWin",500,500,-1,-1);
	base_window* b =
		base_window::createBaseWindow("newWin", 300, 300, 100, 100);

	b->init();
	b->show();

	a->init();
	a->show();

	/*base_window b("window_2", 500, 500, -1, -1);
	b.init();
	b.show();*/

	base_window::processWindows();

	base_window::clearWindowList();

	return 0;
}