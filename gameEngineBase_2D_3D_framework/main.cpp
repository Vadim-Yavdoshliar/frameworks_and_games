
#include "windowSystem.h"

int WINAPI WinMain(HINSTANCE handler, HINSTANCE someTrashMaybe, LPSTR cmdParams, int wndStatus) {
	
	base_window* a = 
		CREATE_b_WINDOW("newWin",500,500,-1,-1)
	base_window* b =
		CREATE_b_WINDOW("newWin2", 300, 300, 100, 100)
	base_window* c =
		CREATE_b_WINDOW("newWin3", 200, 400, 100, 500)

	b->init();
	b->show();

	a->init();
	a->show();

	c->init();
	c->show();

	base_window::processWindows();

	base_window::clearWindowList();

	return 0;
}